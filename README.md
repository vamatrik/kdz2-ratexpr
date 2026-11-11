Не стоило сюда заглядывать 😈😈😈


Но вот как собрать и запустить:
Прописываете для debug в корневой папке:
```bash
cmake -S . -B build-debug -DCMAKE_BUILD_TYPE=Debug && cmake --build build-debug -j
```
Для release:
```bash
cmake -S . -B build-release -DCMAKE_BUILD_TYPE=Release && cmake --build build-release -j
```
Потом как запустить?
```bash
./build-debug/apps/demo_(название приложения)
```
```bash
./build-release/apps/demo_(название приложения)
```
варианты названий: expression, fraction, simplify
Вот я подставил их:
```bash
./build-debug/apps/demo_expression
```
```bash
./build-release/apps/demo_expression
```
```bash
./build-debug/apps/demo_fraction
```
```bash
./build-release/apps/demo_fraction
```
```bash
./build-debug/apps/demo_simplify
```
```bash
./build-release/apps/demo_simplify
```