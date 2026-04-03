// Parking Management System - Laptop Interface Version
// Uses Serial Monitor instead of LCD display
// All components (sensors, LEDs) remain connected to Arduino

// Pins des capteurs ultrasoniques
#define TRIG_ENTREE 7
#define ECHO_ENTREE 8
#define TRIG_SORTIE 9
#define ECHO_SORTIE 10

// Pins des LEDs
#define LED_VERTE 11
#define LED_ROUGE 12

// Variables
int capacite_totale = 3;
int compteur = 0;
bool voiture_entree = false;
bool voiture_sortie = false;
unsigned long lastUpdate = 0;

void setup() {
  // Initialisation des pins
  pinMode(TRIG_ENTREE, OUTPUT);
  pinMode(ECHO_ENTREE, INPUT);
  pinMode(TRIG_SORTIE, OUTPUT);
  pinMode(ECHO_SORTIE, INPUT);
  pinMode(LED_VERTE, OUTPUT);
  pinMode(LED_ROUGE, OUTPUT);
  
  // Initialisation de la communication série pour l'interface laptop
  Serial.begin(9600);
  
  Serial.println("========================================");
  Serial.println("   PARKING MANAGEMENT SYSTEM");
  Serial.println("   Interface: Laptop (Serial Monitor)");
  Serial.println("========================================");
  Serial.println("");
  Serial.println("Systeme initialise avec succes!");
  Serial.println("Capacite totale: " + String(capacite_totale) + " places");
  Serial.println("");
}

void loop() {
  // Mesure distance capteur ENTRÉE
  long distance_entree = mesurer_distance(TRIG_ENTREE, ECHO_ENTREE);
  
  // Mesure distance capteur SORTIE
  long distance_sortie = mesurer_distance(TRIG_SORTIE, ECHO_SORTIE);
  
  // Détection voiture à l'ENTRÉE
  if (distance_entree < 20 && distance_entree > 0 && !voiture_entree) {
    if (compteur < capacite_totale) {
      compteur++;
      voiture_entree = true;
      Serial.println("----------------------------------------");
      Serial.println(">>> Voiture DETECTEE A L'ENTREE");
      Serial.println(">>> Place attribuee!");
    } else {
      Serial.println("----------------------------------------");
      Serial.println(">>> Voiture A L'ENTREE mais PARKING PLEIN!");
      Serial.println(">>> Acces refuse!");
      voiture_entree = true;
    }
    delay(1000);
  }
  
  if (distance_entree > 20 || distance_entree == 0) {
    voiture_entree = false;
  }
  
  // Détection voiture à la SORTIE
  if (distance_sortie < 20 && distance_sortie > 0 && !voiture_sortie) {
    if (compteur > 0) {
      compteur--;
      voiture_sortie = true;
      Serial.println("----------------------------------------");
      Serial.println(">>> Voiture DETECTEE A LA SORTIE");
      Serial.println(">>> Place liberee!");
    }
    delay(1000);
  }
  
  if (distance_sortie > 20 || distance_sortie == 0) {
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
  
  // Affichage sur Serial Monitor (laptop interface)
  unsigned long currentTime = millis();
  if (currentTime - lastUpdate >= 500) { // Update every 500ms
    Serial.println("");
    Serial.println("=== STATUS DU PARKING ===");
    Serial.println("Places disponibles: " + String(places_disponibles) + "/" + String(capacite_totale));
    Serial.println("Places occupees: " + String(compteur));
    
    if (places_disponibles > 0) {
      Serial.println("Status: DISPONIBLE [LED VERTE ON]");
    } else {
      Serial.println("Status: COMPLET [LED ROUGE ON]");
    }
    Serial.println("===========================");
    Serial.println("");
    
    lastUpdate = currentTime;
  }
  
  delay(100);
}

// Fonction de mesure de distance
long mesurer_distance(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  
  long duree = pulseIn(echo, HIGH, 30000); // Timeout de 30ms
  
  if (duree == 0) {
    return 0; // Pas de retour
  }
  
  long distance = duree * 0.034 / 2;
  
  return distance;
}
