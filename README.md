# MQTT C++ example application

Пример кода с использованием библиотеки [Paho] в версии C++.

## Компиляция

### Предварительные требования

#### Ubuntu

 * `build-essenstial`,
 * `libjsoncpp1`,
 * `libjsoncpp-dev`,
 * [paho.mqtt.c] — клиентская библиотека Eclipse Paho MQTT, версия для С,
 * [paho.mqtt.c++] — клиентская библиотека Eclipse Paho MQTT, версия для С++,
 * [args] — библиотека для парсинга аргументов командной строки.

### Cборка

Для сборки приложения используется CMake.

#### Опции сборки

| Опция сборки | Значение по умолчанию | Описание                                |
|:------------:|:---------------------:|:---------------------------------------:|
| BUILD_DOC    | OFF                   | Сборка документации (требуется Doxygen) |

#### Linux

```
git clone git@github.com:Samsung-IoT-Academy/mqtt-cpp-example.git
mkdir build-mqtt-cpp-example
cd build-mqtt-cpp-example
cmake ../mqtt-cpp-example
make
```

## Документация

Документация не создаётся по умолчанию. Чтобы осуществить сборку документации,
необходимо передать опцию `BUILD_DOC` CMake:

```
cmake -DBUILD_DOC=ON ../mqtt-cpp-example
make
```

Используется система документирования Doxygen.

Сборка документации без перекомпиляции приложения.

```
make doc_doxygen
```

[Paho]:https://github.com/eclipse/paho.mqtt.cpp
[paho.mqtt.c]:https://github.com/eclipse/paho.mqtt.c
[paho.mqtt.c++]:https://github.com/eclipse/paho.mqtt.cpp
[args]:https://github.com/Taywee/args
