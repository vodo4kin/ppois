#include <sc-memory/test/sc_test.hpp>
#include <sc-memory/sc_memory.hpp>

#include "../agent/find_optimal_layout_agent.hpp"
#include "../keynodes/pcb_layout_keynodes.hpp"

using AgentTest = ScMemoryTest;
// Тест проверяет, что агент: 1. Находит компоненты и соединения 2. Создает оптимальную раскладку
//3. Связывает ее с компонентами  4. Возвращает не пустой результат
TEST_F(AgentTest, FindOptimalLayoutAgent_BasicSuccess)
{
    // 1. Регистрируем агент в тестовой памяти
    m_ctx->SubscribeAgent<FindOptimalLayoutAgent>();
    
    // 2. Создаем тестовые компоненты
    ScAddr component1 = m_ctx->GenerateNode(ScType::ConstNode);
    ScAddr component2 = m_ctx->GenerateNode(ScType::ConstNode);
    ScAddr component3 = m_ctx->GenerateNode(ScType::ConstNode);
    
    // Устанавливаем, что это электронные компоненты
    m_ctx->GenerateConnector(
        ScType::ConstPermPosArc,
        PcbLayoutKeynodes::concept_electronic_component,
        component1
    );
    m_ctx->GenerateConnector(
        ScType::ConstPermPosArc,
        PcbLayoutKeynodes::concept_electronic_component,
        component2
    );
    m_ctx->GenerateConnector(
        ScType::ConstPermPosArc,
        PcbLayoutKeynodes::concept_electronic_component,
        component3
    );
    
    // 3. Создаем тестовое соединение
    ScAddr connection1 = m_ctx->GenerateNode(ScType::ConstNode);
    
    // Устанавливаем, что это электрическое соединение
    m_ctx->GenerateConnector(
        ScType::ConstPermPosArc,
        PcbLayoutKeynodes::concept_electrical_connection,
        connection1
    );
    
    // 4. Связываем компоненты через соединение
    // Компонент1 соединен с Компонентом2
    m_ctx->GenerateConnector(
        ScType::ConstCommonArc,
        connection1,
        component1
    );
    m_ctx->GenerateConnector(
        ScType::ConstPermPosArc,
        PcbLayoutKeynodes::nrel_connected_to,
        m_ctx->GenerateConnector(
            ScType::ConstCommonArc,
            connection1,
            component1
        )
    );
    
    m_ctx->GenerateConnector(
        ScType::ConstCommonArc,
        connection1,
        component2
    );
    m_ctx->GenerateConnector(
        ScType::ConstPermPosArc,
        PcbLayoutKeynodes::nrel_connected_to,
        m_ctx->GenerateConnector(
            ScType::ConstCommonArc,
            connection1,
            component2
        )
    );
    
    // 5. Создаем действие для агента
    ScAction action = m_ctx->GenerateAction(
        PcbLayoutKeynodes::action_find_optimal_component_layout
    );
    
    // 6. Инициируем действие и ждем завершения
    EXPECT_TRUE(action.InitiateAndWait());
    
    // 7. Проверяем, что действие завершилось успешно
    EXPECT_TRUE(action.IsFinishedSuccessfully());
    
    // 8. Получаем результат
    ScStructure resultStructure = action.GetResult();
    EXPECT_FALSE(resultStructure.IsEmpty());
    
    // 9. Проверяем, что в результате есть оптимальная раскладка
    ScIterator3Ptr itResult = m_ctx->CreateIterator3(
        resultStructure,
        ScType::ConstPermPosArc,
        ScType::ConstNode
    );
    
    bool foundOptimalLayout = false;
    while (itResult->Next())
    {
        ScAddr element = itResult->Get(2);
        
        // Проверяем, является ли элемент оптимальной раскладкой
        ScIterator3Ptr itCheck = m_ctx->CreateIterator3(
            PcbLayoutKeynodes::concept_optimal_layout,
            ScType::ConstPermPosArc,
            element
        );
        if (itCheck->Next())
        {
            foundOptimalLayout = true;
            
            // Проверяем, что оптимальная раскладка связана с компонентами
            ScIterator5Ptr itComponents = m_ctx->CreateIterator5(
                element,
                ScType::ConstCommonArc,
                ScType::ConstNode,
                ScType::ConstPermPosArc,
                PcbLayoutKeynodes::nrel_in_optimal_layout
            );
            
            // Должны быть минимум 2 компонента
            size_t componentCount = 0;
            while (itComponents->Next())
            {
                componentCount++;
            }
            EXPECT_GE(componentCount, 2u);
        }
    }
    
    EXPECT_TRUE(foundOptimalLayout);
    
    // 10. Отписываем агент
    m_ctx->UnsubscribeAgent<FindOptimalLayoutAgent>();
}
  
// Тест: Сценарий без компонентов.
// Проверяем, что агент корректно обрабатывает ситуацию, когда в БЗ нет компонентов
TEST_F(AgentTest, FindOptimalLayoutAgent_NoComponents)
{
    // 1. Регистрируем агент
    m_ctx->SubscribeAgent<FindOptimalLayoutAgent>();
    
    // 2. Создаем действие (без компонентов и соединений)
    ScAction action = m_ctx->GenerateAction(
        PcbLayoutKeynodes::action_find_optimal_component_layout
    );
    
    // 3. Инициируем действие
    EXPECT_TRUE(action.InitiateAndWait());
    
    // 4. Проверяем, что действие завершилось успешно
    EXPECT_TRUE(action.IsFinishedSuccessfully());
    
    // 5. Отписываем агент
    m_ctx->UnsubscribeAgent<FindOptimalLayoutAgent>();
}

// Тест: Проверяем сценарий с 3 компонентами
TEST_F(AgentTest, FindOptimalLayoutAgent_WithPCBSystem)
{
    // 1. Регистрируем агент
    m_ctx->SubscribeAgent<FindOptimalLayoutAgent>();
    
    // 2. Создаем систему (pcb_system)
    ScAddr pcbSystem = m_ctx->GenerateNode(ScType::ConstNode);
    
    // 3. Создаем несколько компонентов для системы
    ScAddr componentU1 = m_ctx->GenerateNode(ScType::ConstNode);
    ScAddr componentU2 = m_ctx->GenerateNode(ScType::ConstNode);
    ScAddr componentR1 = m_ctx->GenerateNode(ScType::ConstNode);
    // Помечаем их, что они электронные компоненты
    m_ctx->GenerateConnector(
        ScType::ConstPermPosArc,
        PcbLayoutKeynodes::concept_electronic_component,
        componentU1
    );
    m_ctx->GenerateConnector(
        ScType::ConstPermPosArc,
        PcbLayoutKeynodes::concept_electronic_component,
        componentU2
    );
    m_ctx->GenerateConnector(
        ScType::ConstPermPosArc,
        PcbLayoutKeynodes::concept_electronic_component,
        componentR1
    );
    
    // 4. Создаем действие
    ScAction action = m_ctx->GenerateAction(
        PcbLayoutKeynodes::action_find_optimal_component_layout
    );
    
    // 5. Инициируем действие
    EXPECT_TRUE(action.InitiateAndWait());
    
    // 6. Проверяем успешное завершение
    EXPECT_TRUE(action.IsFinishedSuccessfully());
    
    // 7. Получаем результат
    ScStructure result = action.GetResult();
    EXPECT_FALSE(result.IsEmpty());
    
    // 8. Отписываем агент
    m_ctx->UnsubscribeAgent<FindOptimalLayoutAgent>();
}
