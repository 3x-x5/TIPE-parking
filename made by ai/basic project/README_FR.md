# Système de Parking Automatisé - Version de Base
## Documentation Complète

### 📋 Description du Projet
Ce projet réalise un système de gestion de parking automatisé simplifié utilisant :
- **2 capteurs ultrasoniques** pour détecter l'entrée et la sortie des véhicules
- **2 LEDs** (verte et rouge) pour indiquer visuellement la disponibilité
- **L'écran de l'ordinateur** (via le Moniteur Série) comme interface d'affichage
- **Arduino Uno** comme contrôleur principal

Le système gère une capacité maximale de **2 places de parking**.

---

### 🔌 Schéma de Câblage

#### Matériel Nécessaire :
- 1 × Arduino Uno
- 2 × Capteurs ultrasoniques HC-SR04
- 1 × LED verte
- 1 × LED rouge
- 2 × Résistances 220Ω (pour les LEDs)
- Fils de connexion (jumpers)
- 1 × Breadboard (plaque d'essai)

#### Connexions Détaillées :

**Capteur Ultrasonique 1 (Entrée) :**
| Pin HC-SR04 | Connection Arduino |
|-------------|-------------------|
| VCC         | 5V                |
| GND         | GND               |
| Trig        | Pin 2             |
| Echo        | Pin 3             |

**Capteur Ultrasonique 2 (Sortie) :**
| Pin HC-SR04 | Connection Arduino |
|-------------|-------------------|
| VCC         | 5V                |
| GND         | GND               |
| Trig        | Pin 4             |
| Echo        | Pin 5             |

**LEDs :**
| Composant | Pin Arduino | Note                    |
|-----------|-------------|-------------------------|
| LED Verte | Pin 6       | Via résistance 220Ω     |
| LED Rouge | Pin 7       | Via résistance 220Ω     |

*Note : La patte longue (+) de la LED se connecte à la pin Arduino via la résistance. La patte courte (-) se connecte au GND.*

---

### 💻 Installation et Configuration

#### Étape 1 : Préparation du Logiciel
1. Téléchargez et installez l'**Arduino IDE** depuis [arduino.cc](https://www.arduino.cc/en/software)
2. Ouvrez l'Arduino IDE
3. Chargez le fichier `basic_parking.ino` dans l'IDE

#### Étape 2 : Câblage
1. Placez l'Arduino et les composants sur la breadboard
2. Réalisez les connexions selon le tableau ci-dessus
3. Vérifiez deux fois toutes les connexions avant de brancher l'USB

#### Étape 3 : Téléchargement du Code
1. Connectez l'Arduino à votre ordinateur via câble USB
2. Dans l'Arduino IDE :
   - Allez dans **Outils > Type de carte** et sélectionnez **Arduino Uno**
   - Allez dans **Outils > Port** et sélectionnez le port COM approprié
3. Cliquez sur le bouton **Téléverser** (flèche droite →)

#### Étape 4 : Utilisation du Moniteur Série
1. Après le téléchargement, cliquez sur l'icône **Moniteur Série** (loupe en haut à droite)
2. Assurez-vous que la vitesse est réglée sur **9600 bauds**
3. Vous verrez apparaître les messages de statut en temps réel

---

### 🚀 Fonctionnement du Système

#### Logique de Détection :
- **Capteur 1 (Entrée)** : Détecte un véhicule qui s'approche de l'entrée
- **Capteur 2 (Sortie)** : Détecte un véhicule qui quitte le parking

#### Gestion des Places :
- Capacité maximale : **2 véhicules**
- Compteur interne suit le nombre de voitures présentes
- Anti-rebond intégré pour éviter les doubles comptages

#### Indicateurs Visuels (LEDs) :
| État du Parking | LED Verte | LED Rouge | Signification |
|-----------------|-----------|-----------|---------------|
| Places libres   | ALLUMÉE   | ÉTEINTE   | Entrez !      |
| Complet         | ÉTEINTE   | ALLUMÉE   | Complet       |

#### Messages sur l'Ordinateur :
Le moniteur série affiche :
- Le nombre de places disponibles
- Les événements "VÉHICULE DÉTECTÉ À L'ENTRÉE" ou "SORTIE"
- Les alertes "PARKING COMPLET" ou "PLACE LIBÉRÉE"
- Un résumé périodique de l'état

---

### 📝 Exemple de Sortie (Moniteur Série)

```
=== SYSTEME DE PARKING AUTOMATISE ===
Capacite totale: 2 places
Initialisation...

[ENTREE] Vehicule detecte !
Places disponibles: 1
Status: Vert (Libre)

[ENTREE] Vehicule detecte !
Places disponibles: 0
Status: Rouge (COMPLET)
*** PARKING COMPLET ***

[SORTIE] Vehicule detecte !
Places disponibles: 1
Status: Vert (Libre)
```

---

### 🔧 Dépannage et Problèmes Courants

| Problème | Cause Possible | Solution |
|----------|----------------|----------|
| Aucune donnée dans le moniteur | Mauvaise vitesse (bauds) | Vérifiez que c'est bien 9600 |
| "Comportement aléatoire" | Mauvais câblage ou alimentation | Vérifiez les connexions 5V/GND |
| Compte trop de voitures | Capteurs trop sensibles | Augmentez la distance de détection dans le code |
| LEDs ne s'allument pas | Polarité inversée ou résistance manquante | Vérifiez le sens des LEDs (+ vers Arduino) |
| Erreur de compilation | Mauvais port ou carte sélectionnée | Vérifiez Outils > Carte et Port |

#### Ajustement de la Sensibilité :
Si les capteurs détectent des objets trop loin, modifiez cette ligne dans le code :
```cpp
if (distance < 15) { // Changez 15 par 10 ou 20 selon vos besoins
```

---

### 🎯 Améliorations Possibles
Pour aller plus loin, vous pourrez ajouter :
- Un servomoteur pour une barrière physique
- Un module RFID pour l'accès sécurisé
- Un écran LCD pour affichage local
- Un buzzer pour des alertes sonores
- Une connexion Bluetooth/Wi-Fi pour surveillance à distance

---

### 📄 Licence
Ce projet est fourni à titre éducatif. Vous êtes libre de modifier et partager ce code.

**Bon courage avec votre projet TIPE !** 🚗🅿️
