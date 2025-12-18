#include "find_optimal_layout_agent.hpp"
#include "keynodes/pcb_layout_keynodes.hpp"

#include <sc-memory/sc_memory.hpp>
#include <sc-memory/sc_iterator.hpp>

#include <vector>
#include <algorithm>

using namespace std;

ScAddr FindOptimalLayoutAgent::GetActionClass() const
{
    return PcbLayoutKeynodes::action_find_optimal_component_layout;
}
//Выполняется, когда действие инициировано
ScResult FindOptimalLayoutAgent::DoProgram(ScAction & action)
{
    m_logger.Debug("FindOptimalLayoutAgent started");

    try
    {
        // 1. Находим все компоненты
        //вектор для хранения sc-адресов найденных компонентов
        vector<ScAddr> components;
        // Создает итератор, который ищет все узлы,которые являются эземплярами понятия электронный компонент
        ScIterator3Ptr itComponents = m_context.CreateIterator3(
            PcbLayoutKeynodes::concept_electronic_component,
            ScType::ConstPermPosArc,
            ScType::ConstNode);

        // Просто цикл по всем найденным компонентам
        while (itComponents->Next())
        {
            // Возвращает сам компонент
            components.push_back(itComponents->Get(2));
        }

        m_logger.Debug("Found " + to_string(components.size()) + " components");

        // 2. Находим все соединения
        // Вектор пар, где два компонента соединены между собой
        vector<pair<ScAddr, ScAddr>> connections;
        ScIterator3Ptr itConnections = m_context.CreateIterator3(
            PcbLayoutKeynodes::concept_electrical_connection,
            ScType::ConstPermPosArc,
            ScType::ConstNode);
        
        // Цикл по каждому соединению, что у нас есть (шина данных и т.д.)
        while (itConnections->Next())
        {
            ScAddr connection = itConnections->Get(2);
            
            // Для каждого соединения находим связанные компоненты
            // ТО ЕСТЬ СОБИРАЕМ ВСЕ КОМПОНЕНТЫ, УЧАСТВУЮЩИЕ В ЭТОМ СОЕДИНЕНИИ
            vector<ScAddr> connectedComps;
            ScIterator5Ptr itConnected = m_context.CreateIterator5(
                connection,
                ScType::ConstCommonArc, //Дуга
                ScType::ConstNode,      //Компонент
                ScType::ConstPermPosArc, //дуга от компонента к отношению
                PcbLayoutKeynodes::nrel_connected_to); //неролевое отношение "соединен с"

            while (itConnected->Next())
            {
                // Закидываем компонент, участвующий в соединении
                connectedComps.push_back(itConnected->Get(2));
            }

            // Добавляем все пары компонентов, соединённых этим соединением
            for (size_t i = 0; i < connectedComps.size(); ++i)
            {
                for (size_t j = i + 1; j < connectedComps.size(); ++j)
                {
                    connections.push_back({connectedComps[i], connectedComps[j]});
                }
            }
        }

        m_logger.Debug("Found " + to_string(connections.size()) + " connections");

        // Если нет компонентов - выводим сообщение, что их нет
        if (components.empty())
        {
            m_logger.Warning("No components found");
            return action.FinishSuccessfully();
        }

        // 3. Упрощённая проверка планарности графа
        // Формула Эйлера для планарных графов: |E| ≤ 3|V| - 6 (для |V| ≥ 3) или В - Р + Г = 2
        bool isPlanar = true;
        // кол-во слоев печатной платы
        int requiredLayers = 1;
        
        if (components.size() >= 3)
        {
            int maxEdgesPlanar = 3 * components.size() - 6;
            
            if (connections.size() > maxEdgesPlanar)
            {
                isPlanar = false;
                // Упрощённая оценка количества слоёв
                requiredLayers = min(4, (int)(connections.size() / maxEdgesPlanar) + 1);
                m_logger.Info("Graph is not planar. Estimated layers required: " + to_string(requiredLayers));
            }
            else
            {
                m_logger.Info("Graph may be planar (E ≤ 3V-6 condition satisfied)");
            }
        }

        // 4. Выбор компонентов для "оптимальной" раскладки
        vector<ScAddr> selectedComponents;
        
        if (!isPlanar && !components.empty())
        {
            // Если граф непланарен, выбираем первые N компонентов для демонстрации
            int toSelect = min(8, (int)components.size());
            for (int i = 0; i < toSelect; ++i)
            {
                selectedComponents.push_back(components[i]);
            }
            m_logger.Info("Selected first " + to_string(toSelect) + " components (graph not planar)");
        }
        else
        {
            // Если планарен или мало соединений, берём все компоненты
            selectedComponents = components;
            m_logger.Info("Selected all " + to_string(components.size()) + " components");
        }

        m_logger.Info("Selected " + to_string(selectedComponents.size()) + 
                     " components for optimal layout");

        // 5. Создаём результат - оптимальную раскладку
        // Создаем новый узел - это будет оптимальная компоновка
        ScAddr optimalLayout = m_context.GenerateNode(ScType::ConstNode);
        
        // Устанавливаем, что это экземпляр concept_optimal_layout
        m_context.GenerateConnector(
            ScType::ConstPermPosArc,
            PcbLayoutKeynodes::concept_optimal_layout,
            optimalLayout
        );
        
        // Добавляем основной идентификатор
        ScAddr mainIdtfLink = m_context.GenerateLink();
        string idtfText = "Optimal layout of " + to_string(selectedComponents.size()) + 
                         " components, planar: " + (isPlanar ? "yes" : "no") +
                         ", layers: " + to_string(requiredLayers);
        m_context.SetLinkContent(mainIdtfLink, idtfText);
        
        //Связываем узел раскладки с тектовым идентификатором выше
        m_context.GenerateConnector(
            ScType::ConstPermPosArc,
            optimalLayout,
            mainIdtfLink
        );

        // Указываем, что это основной идентификатор
        m_context.GenerateConnector(
            ScType::ConstPermPosArc,
            PcbLayoutKeynodes::nrel_main_idtf,
            m_context.GenerateConnector(
                ScType::ConstCommonArc,
                optimalLayout,
                mainIdtfLink
            )
        );

        // 6. Связываем выбранные компоненты с оптимальной раскладкой через отношение nrel_in_optimal_layout
        for (const auto& component : selectedComponents)
        {
            // Создаем связь: optimalLayout -> component
            ScAddr arc = m_context.GenerateConnector(
                ScType::ConstCommonArc,
                optimalLayout,
                component
            );
            
            // Указываем, что это отношение оптимальной раскладки
            m_context.GenerateConnector(
                ScType::ConstPermPosArc,
                PcbLayoutKeynodes::nrel_in_optimal_layout,
                arc
            );
            
            m_logger.Debug("Added component to optimal layout");
        }

        // 7. Создаем структуру результата с оптимальной раскладкой
        ScStructure result = m_context.GenerateStructure();
        result << optimalLayout;
        
        // Добавляем все компоненты в результат
        for (const auto& component : selectedComponents)
        {
            result << component;
        }

        // Устанавливаем структуру как результат действия
        action.SetResult(result);

        m_logger.Debug("FindOptimalLayoutAgent finished successfully");
        return action.FinishSuccessfully();
    }
    // Отловили ошибку - выбрасываем исключние FindOptimalLayoutAgent Error
    catch (std::exception const & e)
    {
        // Ошибка! логируем и завершаем
        m_logger.Error("FindOptimalLayoutAgent error: " + string(e.what()));
        return action.FinishWithError();
    }
}
