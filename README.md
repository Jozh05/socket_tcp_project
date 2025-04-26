# Socket TCP Project

Консольное приложение и серверы на C++ с использованием сырых POSIX-сокетов, реализующие трёхзвенный пайплайн: клиент → сервер обработки → сервер отображения результата.

---

## 📦 Зависимости
- **CMake** ≥ 3.15
- **C++20**
- **gtest**

Для сборки проекта необходимо установить библиотеку **gtest**

Вы можете установить её с помощью [vcpkg](https://github.com/Microsoft/vcpkg):

```bash
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh
./vcpkg integrate install
./vcpkg install gtest
```
Далее при сборке через CMake необходимо использовать ключ, напечатанный при выполнении команды
```bash
./vcpkg integrate install
```

## ⚙️ Сборка проекта

Для сборки выполните следующие действия, находясь в корне проекта

```bash
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=/path/to/your/toolchain/file
make
```

## Запуск модулей
```
./display_server <display_port>
```
Здесь **display_port** - порт, который будет слушать сервер отображения
```
./processing_server <processing_port> <display_host> <display_port>
```
Здесь **processing_port** - порт, который будет слушать сервер обработки данных

**display_host** - IP адрес сервера отображения результата

**display_port** - порт, к которому будет подключаться сервер обработки данных
```
./console_client <processing_host> <processing_port>
```
Здесь **processing_host** - IP адрес сервера обработки данных

**processing_port** - порт, к которому будет подключаться клиентское приложение


## Пример использования

#### В одном терминале:
```
./display_server 7002
```
#### Во втором:
```
./processing_server 7001 127.0.0.1 7002
```
#### В третьем:
```
./console_client 127.0.0.1 7001
> hello world hello
Display server: Processed result: hello world
```
