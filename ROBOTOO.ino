// ==========================================
// ROBOT SUIVEUR DE LIGNE (3 CAPTEURS + VITESSE PWM)
// ==========================================

// --- 1. DÉFINITION DES PINS ---

// Les Moteurs (Direction)
const int IN1 = 5;
const int IN2 = 6;
const int IN3 = 9;
const int IN4 = 10;

// Les Moteurs (Vitesse - PWM) - NOUVEAU !
const int ENA = 3;   // Vitesse Moteur Gauche (Doit être sur un pin PWM ~)
const int ENB = 11;  // Vitesse Moteur Droit (Doit être sur un pin PWM ~)

// Les Capteurs
const int CapteurG = 2; // Gauche
const int CapteurC = 7; // Centre (ATTENTION : Changé du pin 3 vers 7 !)
const int CapteurD = 4; // Droite

// --- 2. RÉGLAGES ---
const int LIGNE = HIGH; // HIGH pour ligne noire, LOW pour ligne blanche

// VITESSE DU ROBOT (Entre 0 et 255)
// 0 = Arrêt, 255 = Vitesse Max
int vitesse = 130;        // Vitesse en ligne droite
int vitesseTourne = 110;  // Vitesse plus lente pour tourner (plus précis)

void setup() {
  Serial.begin(9600);

  // Configuration des Moteurs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT); // Nouveau
  pinMode(ENB, OUTPUT); // Nouveau

  // Configuration des Capteurs
  pinMode(CapteurG, INPUT);
  pinMode(CapteurC, INPUT);
  pinMode(CapteurD, INPUT);

  delay(2000); // Pause de sécurité au démarrage
}

void loop() {
  // Lecture des capteurs
  int valG = digitalRead(CapteurG);
  int valC = digitalRead(CapteurC);
  int valD = digitalRead(CapteurD);

  // --- LOGIQUE DE DÉCISION ---

  // CAS 1 : Tout droit (Ligne au centre)
  if (valC == LIGNE && valG != LIGNE && valD != LIGNE) {
    avancer();
  }
  
  // CAS 2 : Correction vers la Gauche
  else if (valG == LIGNE) {
    tournerGauche();
  }

  // CAS 3 : Correction vers la Droite
  else if (valD == LIGNE) {
    tournerDroite();
  }

  // CAS 4 : Arrêt (Intersection ou perdu)
  else if (valG == LIGNE && valC == LIGNE && valD == LIGNE) {
    stopper();
  }
  else {
    stopper(); // Ou mettre avancer() doucement si tu veux qu'il cherche
  }
}

// ==========================================
// --- FONCTIONS DE MOUVEMENT (AVEC VITESSE) ---
// ==========================================

void avancer() {
  // On active la puissance (PWM)
  analogWrite(ENA, vitesse);
  analogWrite(ENB, vitesse);
  
  // Sens de rotation : Avant
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void tournerGauche() {
  // On réduit un peu la vitesse pour mieux tourner
  analogWrite(ENA, vitesseTourne);
  analogWrite(ENB, vitesseTourne);

  // Gauche recule, Droit avance
  digitalWrite(IN1, LOW);  
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void tournerDroite() {
  // On réduit un peu la vitesse pour mieux tourner
  analogWrite(ENA, vitesseTourne);
  analogWrite(ENB, vitesseTourne);

  // Gauche avance, Droit recule
  digitalWrite(IN1, HIGH); 
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  
  digitalWrite(IN4, HIGH);
}

void stopper() {
  // Vitesse à 0
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}