# MEE
## Cel Systemu
Celem systemu jest stworzenie zaawansowanego silnika fizycznego do symulacji zachowań cieczy. System ma umożliwić programistom i grafikom tworzenie realistycznych animacji cieczy, takich jak woda czy olej, poprzez precyzyjne odwzorowanie fizycznych właściwości płynów.

## Zakres Systemu
### Funkcje Główne
---
1. **Symulacja Zachowania Cieczy:**
	- Precyzyjna symulacja ruchu cieczy z uwzględnieniem grawitacji, kolizji i innych właściwości fizycznych.
	- Interakcje między cząstkami cieczy, takie jak kolizje i rozprzestrzenianie się fal.

2. **Renderowanie Grafiki:**
	- Wizualizacja cieczy w czasie rzeczywistym z wykorzystaniem biblioteki zewnętrznej (prawdopodbonie SFML).

3. **Interakcje Zewnętrzne:**
	- Możliwość interakcji z obiektami zewnętrznymi, takimi jak przeszkody, wpływającymi na zachowanie cieczy.

### Funkcje Dodatkowe
---
1. **Edytor Cieczy:**
	- Graficzny interfejs do konfiguracji właściwości cieczy, takich jak gęstość, temperatura, czy kolor.
	- Narzędzia do manipulacji i kształtowania bieżącej symulacji.

2. **Wsparcie Dla Różnych Środowisk:**
	- Możliwość dostosowania parametrów symulacji do różnych warunków środowiskowych, takich jak ciśnienie atmosferyczne czy temperatura.

## Wymagania Funkcjonalne
1. **Symulacja Cząstkowa:**
	- System powinien obsługiwać duże ilości cząstek cieczy, zapewniając jednocześnie płynność działania.

2. **Dokładność Fizyczna:**
	- Symulacja powinna odzwierciedlać realistyczne zachowanie cieczy zgodnie z prawami fizyki.

3. **Rozbudowane Renderowanie:**
	- Renderowanie powinno umożliwiać użycie zaawansowanych efektów wizualnych dla jak największego realizmu.

4. **Interakcje Zewnętrzne:**
	- System powinien reagować na interakcje użytkownika i zewnętrznych obiektów, wpływając na symulację.

5. **Konfiguracja Parametrów:**
	- Umożliwienie dostosowania parametrów cieczy i symulacji poprzez interfejs programistyczny.

## Wymagania Niefunkcjonalne
1. **Wydajność:**
	- System powinien być wydajny, umożliwiając płynne działanie symulacji nawet przy dużej liczbie cząstek.

2. **Stabilność:**
	- System powinien być stabilny i odporny na błędy, minimalizując ryzyko awarii.

3. **Dokumentacja:**
	- Pełna dokumentacja techniczna i użytkownika dla ułatwienia integracji i korzystania z systemu.

5. **Rozszerzalność:**
	- Zapewnienie łatwej rozszerzalności systemu poprzez dodawanie nowych funkcji czy modyfikowanie istniejących.

## Budowa i Użytkowanie

Jeśli korzystasz z systemu Linux, zainstaluj zależności SFML za pomocą menedżera pakietów systemu. Na Ubuntu i innych dystrybucjach opartych na Debianie, możesz użyć następujących poleceń:
```
	sudo apt update
	sudo apt install \
		libxrandr-dev \
		libxcursor-dev \
		libudev-dev \
		libfreetype-dev \
		libopenal-dev \
		libflac-dev \
		libvorbis-dev \
		libgl1-mesa-dev \
		libegl1-mesa-dev
```

### Budowa
1. **Dla systemów Linux i macOS**
```
	cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
	cmake --build build
```
2. **Dla Systemów Windows**
```
	cmake -S . -B build
	cmake --build build --config Release
```

### Użytkowanie
Aby odpalić program należy użyć:
```
	./build/bin/Release/PhysicsEngine.exe
```

## Pipeline
### Jobs: 
- build - Checks project build on Linux, Mac OS and Windows. Runs of workflow_dispatch ([trigger manually](https://docs.github.com/en/actions/using-workflows/manually-running-a-workflow#running-a-workflow))