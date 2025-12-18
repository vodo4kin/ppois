#pragma once

#include <sc-memory/sc_keynodes.hpp>

// Создаём класс, объединяющий ключевые sc-элементы, используемые
// агентами в рамках одного модуля.
// Наследуем его от базового класса ScKeynodes.
/*
    В системе OSTIS все важные понятия (например, "электронный компонент",
    "действие поиска оптимальной раскладки") представлены в виде узлов в
    семантическом графе. Чтобы работать с ними в C++-коде, нужно знать их
    внутренние адреса (ScAddr). 

    Вместо того чтобы искать эти адреса каждый раз вручную, OSTIS предоставляет
    механизм "ключевых узлов" (keynodes). Этот класс определяет, какие именно
    sc-идентификаторы (имена из SCS-файлов) нам нужны и какого они типа.
*/
class PcbLayoutKeynodes : public ScKeynodes
{
public:
    // Действие "поиск оптимальной компоновки компонентов"
    static inline ScKeynode const action_find_optimal_component_layout{
        "action_find_optimal_component_layout", ScType::ConstNodeClass};
    // Отношение "Входит в систему" Используется для связывания компонентов с результатом
    static inline ScKeynode const nrel_in_optimal_layout{
        "nrel_in_optimal_layout", ScType::ConstNodeNonRole};
    // Соединен с. Описывает связь между компонентами
    static inline ScKeynode const nrel_connected_to{
        "nrel_connected_to", ScType::ConstNodeNonRole};
    // Класс компонентов (по типу резисторов)
    static inline ScKeynode const concept_electronic_component{
        "concept_electronic_component", ScType::ConstNodeClass};
    // Класс для описания шин, сигналов, групп компонентов, соединенных вместе
    static inline ScKeynode const concept_electrical_connection{
        "concept_electrical_connection", ScType::ConstNodeClass};
    // Наш результат - оптимальная компоновка, содержащая компоненты в опимальном размещении
    static inline ScKeynode const concept_optimal_layout{
        "concept_optimal_layout", ScType::ConstNodeClass};
    
    // Здесь первым аргументом конструктора является системный
    // sc-идентификатор ключевого sc-элемента, а второй аргумент –
    // тип этого sc-элемента.
    // Если в sc-памяти нет ключевого sc-элемента с таким системным
    // sc-идентификатором, то в ней будет создан sc-элемент с таким
    // системным sc-идентификатором и указанным типом.
};
