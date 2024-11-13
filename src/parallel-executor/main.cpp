#include "EventQueue.h"
#include "Reader.h"
#include "Hierarchy.h"
#include "includes.h"

#include <iostream>

/*!
 * \brief описание аргументов функции
 * \param[in] -readA - количество считываний с утсройства А
 * \param[in] -readB - количество считываний с утсройства B
 * \param[in] -crushA - количество итераций, которое пройдет до того, как устройство А сломается
 * \param[in] -crushB - количество итераций. которое пройдет до того, как устройство B сломается
 * \param[in] -duration - время ожидания, если очередь пуста
 */

int main(int argc, char* argv[]) // возможные аргументы: -readA, -readB, -crushA, -crushB, -duration
{
  try
  {
    size_t callCountReadA = SIZE_MAX;
    size_t callCountReadB = SIZE_MAX;
    size_t crushA = SIZE_MAX;
    size_t crushB = SIZE_MAX;
    size_t duration = 6;
    
    if (argc > 1)
    {
      for (int i = 1; i < argc; i += 2)
      {
          if (argv[i] == "-readA")
            callCountReadA = std::stoi(argv[i + 1]);
          if (argv[i] == "-readB")
            callCountReadB = std::stoi(argv[i + 1]);
          if (argv[i] == "-crushA")
            crushA = std::stoi(argv[i + 1]);
          if (argv[i] == "-crushB")
            crushA = std::stoi(argv[i + 1]);
          if (argv[i] == "-duration")
            duration = std::stoi(argv[i + 1]);
      }
    }

    std::cout << "loopCountA was set to " << callCountReadA << "\n";
    std::cout << "loopCountB was set to " << callCountReadB << "\n";
    std::cout << "crushIndexA was set to " << crushA << "\n";
    std::cout << "crushIndexB was set to " << crushB << "\n";
    std::cout << "duration was set to " << duration << "\n";

    Reader reader(std::make_shared<EventQueue>(), std::make_shared<DeviceA>(), std::make_shared<DeviceB>());
    reader.run(callCountReadA, callCountReadB, crushA, crushB, duration);
  }
  catch(std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }
  return 0;
}