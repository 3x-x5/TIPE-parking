Le code utiliser dans la sumilation:


#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Configuration LCD I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pins des capteurs
#define TRIG_ENTREE 2
#define ECHO_ENTREE 3
#define TRIG_SORTIE 4
#define ECHO_SORTIE 5

// Pins des LEDs
#define LED_VERTE 7
#define LED_ROUGE 8

// Variables
int capacite_totale = 3;
int compteur = 0;
bool voiture_entree = false;
bool voiture_sortie = false;

void setup() {
  // Initialisation des pins
  pinMode(TRIG_ENTREE, OUTPUT);
  pinMode(ECHO_ENTREE, INPUT);
  pinMode(TRIG_SORTIE, OUTPUT);
  pinMode(ECHO_SORTIE, INPUT);
  pinMode(LED_VERTE, OUTPUT);
  pinMode(LED_ROUGE, OUTPUT);
  
  // Initialisation LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Parking Manager");
  delay(2000);
  lcd.clear();
  
  Serial.begin(9600);
  Serial.println("Systeme initialise");
}

void loop() {
  // Mesure distance capteur ENTRÉE
  long distance_entree = mesurer_distance(TRIG_ENTREE, ECHO_ENTREE);
  
  // Mesure distance capteur SORTIE
  long distance_sortie = mesurer_distance(TRIG_SORTIE, ECHO_SORTIE);
  
  // Détection voiture à l'ENTRÉE
  if (distance_entree < 20 && !voiture_entree) {
    compteur++;
    voiture_entree = true;
    Serial.println("Voiture ENTREE");
    delay(1000);
  }
  
  if (distance_entree > 20) {
    voiture_entree = false;
  }
  
  // Détection voiture à la SORTIE
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
  
  // Calcul places disponibles
  int places_disponibles = capacite_totale - compteur;
  
  // Gestion des LEDs
  if (places_disponibles > 0) {
    digitalWrite(LED_VERTE, HIGH);
    digitalWrite(LED_ROUGE, LOW);
  } else {
    digitalWrite(LED_VERTE, LOW);
    digitalWrite(LED_ROUGE, HIGH);
  }
  
  // Affichage sur LCD
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
  
  delay(100);
}

// Fonction de mesure de distance
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
