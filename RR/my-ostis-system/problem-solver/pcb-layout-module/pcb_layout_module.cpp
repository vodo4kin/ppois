#include "pcb_layout_module.h"
#include "agent/find_optimal_layout_agent.hpp"
/*Регистрация модуля и агентов в системе OSTIS
Этот файл — точка входа
Что делает этот макрос:
1. Объявляет, что класс `PcbLayoutModule` является валидным модулем
2. Регистрирует этот модуль в глобальном реестре модулей системы.
3. Позволяет ядру автоматически загружать и инициализировать модуль при старте.*/
SC_MODULE_REGISTER(PcbLayoutModule)
    ->Agent<FindOptimalLayoutAgent>();
