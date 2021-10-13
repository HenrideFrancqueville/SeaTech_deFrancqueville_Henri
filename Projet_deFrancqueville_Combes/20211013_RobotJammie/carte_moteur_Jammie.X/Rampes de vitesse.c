
void PWMUpdateSpeed()
{
// Cette fonction est appelée sur timer et permet de suivre des rampes d?accélération
if (robotState.vitesseDroiteCommandeCourante < robotState.vitesseDroiteConsigne)
robotState.vitesseDroiteCommandeCourante = Min(
robotState.vitesseDroiteCommandeCourante + acceleration,
robotState.vitesseDroiteConsigne);
if (robotState.vitesseDroiteCommandeCourante > robotState.vitesseDroiteConsigne)
robotState.vitesseDroiteCommandeCourante = Max(
robotState.vitesseDroiteCommandeCourante ? acceleration,
robotState.vitesseDroiteConsigne);

if (robotState.vitesseDroiteCommandeCourante > 0)
{
MOTEUR_DROIT_L_PWM_ENABLE = 0; //pilotage de la pin en mode IO
MOTEUR_DROIT_L_IO_OUTPUT = 1; //Mise à 1 de la pin
MOTEUR_DROIT_PWM_ENABLE_H = 1; //Pilotage de la pin en mode PWM
}
else
{
MOTEUR_DROIT_H_PWM_ENABLE = 0; //pilotage de la pin en mode IO
MOTEUR_DROIT_H_IO_OUTPUT = 1; //Mise à 1 de la pin
MOTEUR_DROIT_L_PWM_ENABLE = 1; //Pilotage de la pin en mode PWM
}
MOTEUR_DROIT_DUTY_CYCLE = Abs(robotState.vitesseDroiteCommandeCourante)*PWMPER;

if (robotState.vitesseGaucheCommandeCourante < robotState.vitesseGaucheConsigne)
robotState.vitesseGaucheCommandeCourante = Min(
robotState.vitesseGaucheCommandeCourante + acceleration,
robotState.vitesseGaucheConsigne);
if (robotState.vitesseGaucheCommandeCourante > robotState.vitesseGaucheConsigne)
robotState.vitesseGaucheCommandeCourante = Max(
robotState.vitesseGaucheCommandeCourante ? acceleration,
robotState.vitesseGaucheConsigne);

if (robotState.vitesseGaucheCommandeCourante > 0)
{
MOTEUR_GAUCHE_L_PWM_ENABLE = 0; //pilotage de la pin en mode IO
MOTEUR_GAUCHE_L_IO_OUTPUT = 1; //Mise à 1 de la pin
MOTEUR_GAUCHE_H_PWM_ENABLE = 1; //Pilotage de la pin en mode PWM
}
else
{
MOTEUR_GAUCHE_H_PWM_ENABLE = 0; //pilotage de la pin en mode IO
MOTEUR_GAUCHE_H_IO_OUTPUT = 1; //Mise à 1 de la pin
MOTEUR_GAUCHE_L_PWM_ENABLE = 1; //Pilotage de la pin en mode PWM
}
MOTEUR_GAUCHE_DUTY_CYCLE = Abs(robotState.vitesseGaucheCommandeCourante) * PWMPER;
}