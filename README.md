# Simple74HC595
 
Bibliothèque Arduino simple et légère pour piloter des registres à décalage **74HC595** en daisy-chain.
 
## Caractéristiques
 
- Supporte jusqu'à **10 registres** en cascade (80 sorties)
- API claire avec application immédiate ou différée
- **Optimisée en mémoire** : 10 octets pour 80 sorties (manipulation par masques de bits)
- Validation des bornes intégrée
- Compatible Arduino Uno, Mega, Nano, ESP8266, ESP32…
---
 
## Brochage
 
| Broche 74HC595 | Nom    | Description                        |
|:--------------:|--------|------------------------------------|
| 14             | DS     | Entrée série des données           |
| 12             | STCP   | Latch clock (applique les données) |
| 11             | SHCP   | Shift clock (décalage)             |
| 10             | MR     | Reset (relier à VCC)               |
| 13             | OE     | Output Enable (relier à GND)       |
| 8              | GND    | Masse                              |
| 16             | VCC    | Alimentation 3.3V ou 5V            |
 
Pour la mise en **daisy-chain**, relier la broche **Q7'** (pin 9) du premier 74HC595 à la broche **DS** (pin 14) du suivant. Les broches STCP et SHCP sont partagées entre tous les registres.
 
---
 
## Installation
 
### Via PlatformIO
 
```ini
; platformio.ini
lib_deps =
    boby15000/Simple74HC595
```
 
### Manuellement
 
Copier le dossier `Simple74HC595` dans le répertoire `libraries/` de votre Arduino IDE.
 
---
 
## Utilisation
 
### Initialisation
 
```cpp
#include <Simple74HC595.h>
 
// Simple74HC595(pin_DS, pin_STCP, pin_SHCP, nombreRegistres = 1)
Simple74HC595 hc(12, 13, 11);        // 1 registre (8 sorties)
Simple74HC595 hc(12, 13, 11, 3);     // 3 registres en daisy-chain (24 sorties)
```
 
### Méthodes disponibles
 
| Méthode                          | Description                                               |
|----------------------------------|-----------------------------------------------------------|
| `Set(pin, etat)`                 | Définit l'état d'une sortie et applique immédiatement     |
| `SetAll(etat)`                   | Définit l'état de toutes les sorties et applique          |
| `SetNoUpdate(pin, etat)`         | Définit l'état d'une sortie sans appliquer                |
| `SetAllNoUpdate(etat)`           | Définit l'état de toutes les sorties sans appliquer       |
| `Toggle(pin)`                    | Inverse l'état d'une sortie et applique                   |
| `RefreshRegister()`              | Applique les états en attente vers le(s) 74HC595          |
 
> **Astuce** : Utilisez `SetNoUpdate()` + `RefreshRegister()` pour modifier plusieurs sorties en une seule transmission, ce qui est plus rapide que d'appeler `Set()` plusieurs fois.
 
---
 
## Exemples
 
### Chenillard simple
 
```cpp
#include <Arduino.h>
#include <Simple74HC595.h>
 
Simple74HC595 hc(12, 13, 11);
 
void setup() {
    hc.SetAll(false);
}
 
void loop() {
    // Allumage progressif
    for (int i = 0; i < 8; i++) {
        hc.Set(i, true);
        delay(500);
    }
 
    delay(2500);
 
    // Extinction progressive
    for (int i = 0; i < 8; i++) {
        hc.Set(i, false);
        delay(500);
    }
}
```
 
### Mise à jour groupée (plus efficace)
 
```cpp
// Allumer les sorties 0, 2, 4, 6 en une seule transmission
hc.SetAllNoUpdate(false);
hc.SetNoUpdate(0, true);
hc.SetNoUpdate(2, true);
hc.SetNoUpdate(4, true);
hc.SetNoUpdate(6, true);
hc.RefreshRegister(); // Une seule transmission pour les 4 changements
```
 
### Daisy-chain (2 registres, 16 sorties)
 
```cpp
Simple74HC595 hc(12, 13, 11, 2);
 
// La sortie 0 est Q0 du premier registre
// La sortie 8 est Q0 du second registre
hc.Set(0, true);
hc.Set(15, true);
```
 
---
 
## Licence
 
MIT — voir fichier [LICENSE](LICENSE)
