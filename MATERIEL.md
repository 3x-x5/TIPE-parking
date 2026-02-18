# Liste du matériel

## Composants principaux

- **Arduino Uno R3**
  - le cerveau du système qui contrôle tout

- **2× Capteur ultrason HC-SR04**
  - détecte les voitures qui entrent et sortent

- **Module RFID RC522 + cartes**
  - lit les badges pour vérifier si la personne a l'accès

- **Servo moteur SG90**
  - fait bouger la barrière pour l'ouvrir et la fermer

- **Écran LCD 16x2 avec I2C**
  - affiche le nombre de places disponibles

## Composants électroniques

- **LED verte + LED rouge**
  - LED verte = accès autorisé ou places dispo
  - LED rouge = accès refusé ou parking plein

- **2× Résistances 220Ω**
  - protègent les LEDs pour pas qu'elles grillent

- **2× Boutons poussoirs**
  - un pour le mode manuel et un pour reset le compteur

## Câblage

- **Breadboard 830 points**
  - pour monter le circuit sans soudure (sinon j'aimerais bien apprendre à faire la soudure si vous avez le matériel)
    
- **Câbles Dupont**
  - pour connecter tous les composants ensemble

- **Câble USB A vers B**
  - pour brancher l'Arduino à l'ordi et upload le code
