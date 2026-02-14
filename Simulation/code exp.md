# Explication du code

## Les bibliothèques
```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
```
Ces bibliothèques permettent de communiquer avec l'écran LCD via le protocole I2C (seulement 2 fils au lieu de 16)

## Configuration des pins
```cpp
#define TRIG_ENTREE 2
#define ECHO_ENTREE 3
#define TRIG_SORTIE 4
#define ECHO_SORTIE 5
#define LED_VERTE 7
#define LED_ROUGE 8
```
On définit quel pin de l'Arduino est connecté à quel composant

## Les variables
```cpp
int capacite_totale = 100;
int compteur = 0;
bool voiture_entree = false;
bool voiture_sortie = false;
```
- `capacite_totale` : nombre total de places dans le parking
- `compteur` : nombre de voitures actuellement dans le parking
- `voiture_entree/sortie` : pour éviter de compter plusieurs fois la même voiture

## La fonction setup()
S'exécute une seule fois au démarrage
```cpp
void setup() {
  pinMode(TRIG_ENTREE, OUTPUT);
  pinMode(ECHO_ENTREE, INPUT);
  pinMode(TRIG_SORTIE, OUTPUT);
  pinMode(ECHO_SORTIE, INPUT);
  pinMode(LED_VERTE, OUTPUT);
  pinMode(LED_ROUGE, OUTPUT);
  
  lcd.init();
  lcd.backlight();
  lcd.print("Parking Manager");
  
  Serial.begin(9600);
}
```
Configure les pins, initialise l'écran LCD et affiche le message de démarrage

## La fonction loop()
Tourne en boucle infinie

### 1. Mesurer les distances
```cpp
long distance_entree = mesurer_distance(TRIG_ENTREE, ECHO_ENTREE);
long distance_sortie = mesurer_distance(TRIG_SORTIE, ECHO_SORTIE);
```
Appelle la fonction pour mesurer la distance avec chaque capteur

### 2. Détecter une voiture à l'entrée
```cpp
if (distance_entree < 20 && !voiture_entree) {
  compteur++;
  voiture_entree = true;
  Serial.println("Voiture ENTREE");
  delay(1000);
}

if (distance_entree > 20) {
  voiture_entree = false;
}
```
Si il y a quelque chose à moins de 20 cm et qu'on a pas déjà compté cette voiture, on incrémente le compteur. Quand la voiture est partie on reset le flag pour être prêt pour la prochaine.

### 3. Détecter une voiture à la sortie
```cpp
if (distance_sortie < 20 && !voiture_sortie) {
  if (compteur > 0) {
    compteur--;
  }
  voiture_sortie = true;
  Serial.println("Voiture SORTIE");
  delay(1000);
}

if (distance_sortie > 20) {
  voiture_sortie = false;
}
```
Même logique que l'entrée mais on décrémente le compteur. On vérifie que le compteur est > 0 pour éviter d'avoir des valeurs négatives.

### 4. Calculer les places disponibles
```cpp
int places_disponibles = capacite_totale - compteur;
```
Simple soustraction entre la capacité totale et le nombre de voitures actuellement dans le parking

### 5. Gérer les LEDs
```cpp
if (places_disponibles > 0) {
  digitalWrite(LED_VERTE, HIGH);
  digitalWrite(LED_ROUGE, LOW);
} else {
  digitalWrite(LED_VERTE, LOW);
  digitalWrite(LED_ROUGE, HIGH);
}
```
Si il y a des places disponibles on allume la LED verte, sinon on allume la LED rouge

### 6. Afficher sur le LCD
```cpp
lcd.setCursor(0, 0);
lcd.print("Places: ");
lcd.print(places_disponibles);
lcd.print("/");
lcd.print(capacite_totale);
lcd.print("  ");

lcd.setCursor(0, 1);
lcd.print("Occupees: ");
lcd.print(compteur);
lcd.print("  ");
```
Affiche le nombre de places disponibles sur la première ligne et le nombre de places occupées sur la deuxième ligne. Les espaces à la fin servent à effacer les anciens caractères.

### 7. Attendre un peu
```cpp
delay(100);
```
Attendre 100 millisecondes avant de recommencer la boucle

## La fonction mesurer_distance()
```cpp
long mesurer_distance(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  
  long duree = pulseIn(echo, HIGH);
  long distance = duree * 0.034 / 2;
  
  return distance;
}
```

### Comment ça marche
1. On envoie un pulse de 10 microsecondes sur le pin TRIG
2. Le capteur envoie des ultrasons
3. Les ultrasons rebondissent sur l'obstacle
4. On lit la durée du signal sur le pin ECHO avec `pulseIn()`
5. On calcule la distance avec la formule : `distance = duree * 0.034 / 2`
   - 0.034 = vitesse du son en cm/microseconde
   - On divise par 2 car le son fait un aller-retour

## Logique du comptage
```
Voiture arrive → distance < 20 cm
              → voiture_entree = false (pas encore comptée)
              → compteur++
              → voiture_entree = true (maintenant comptée)

Voiture encore là → distance < 20 cm
                  → voiture_entree = true
                  → on compte pas (déjà comptée)

Voiture partie → distance > 20 cm
              → voiture_entree = false
              → prêt pour la prochaine voiture
```
