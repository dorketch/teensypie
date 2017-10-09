

/*
 * Version 2 = 
 * J'ai changé les touches directionnels pour mettre directement 
 * les flèches du clavier, c'est plus simple pour aller modifier
 * des configurations ncurse.
 * 
 * Version 1 = 
 * Adapté du code original utilisé sur le site de sudomod. 
 * J'ai modifié les touches utilisés et ajouté des commentaires.
 * C'est celui que j'ai utilisé pour mon gameboy !!!
 */

//Pour canceller au niveau software le noise quand 
//on appuye sur un bouton on inclus la librairie bounce
#include <Bounce2.h>

#include <Keyboard.h>
// Variable du nombre de boutons total pour la définition automatique
//des touches.
#define NUM_KEYS 12
// pour s'assurer que les entré mémoire reste près l'une de l'autre 
//pour que le code soit plus rapide
struct Key {
  long keycode;
  Bounce* bounce;
};

Key keys[NUM_KEYS];
/*définition de la fonction key() qui 
 *fabrique pinMode(num_de_pin, INPUT_PULLUP); 
 *de manière automatique.
*/
Key key(long keycode, int pin) {
  Key *ret = new Key;
  ret->keycode = keycode;
  ret->bounce = new Bounce(pin, 10);
  pinMode(pin, INPUT_PULLUP);
  return *ret;
}
//définition des touches du "clavier" utilisés
void setupKeys() {
  keys[0] = key(KEY_UP, 0); // (keycode 218 = fleche haut) up - tx
  keys[1] = key(KEY_LEFT, 1); // (keycode 216 = fleche gauche )left - rx
  keys[2] = key(KEY_DOWN, 2); // (keycode 217 = fleche bas) down - 2
  keys[3] = key(KEY_RIGHT, 3); // (keycode 215 fleche droite) right - 3
  keys[4] = key(KEY_ESC, 4); //(keycode 177 = escape ) select - 4
  keys[5] = key(KEY_RETURN, 5); //(keycode 176 = enter) start - 5
  keys[6] = key('i', 6); // x - 6
  keys[7] = key('o', 7); // y - 7
  keys[8] = key('y', 8); // b - 8
  keys[9] = key('u', 9); // a - 9
  keys[10] = key('t',10); // left bumper
  keys[11] = key('p',11); // right bumper
}

void setup() {
//on appel la fonction de définition des touches
  setupKeys();
//on lance la communication usb/clavier
  Keyboard.begin();
  //  pinMode(0, INPUT_PULLUP);
}

void loop() {
  /*boucle pour générer les touches automatique.
   * Quand on appuye on envoye la touche, quand on relache
   * on arrète d'envoyer la touche.
   * donc fallingEdge et risingEdge sont l'équivalent de 
   * digitalRead(x)==LOW et digitalRead(x)==HIGH avec la librairie bounce.
  */
  for (int i = 0; i < NUM_KEYS; i++) {
    keys[i].bounce->update();
    if (keys[i].bounce->fallingEdge()) {
      Keyboard.press(keys[i].keycode);
    } else if (keys[i].bounce->risingEdge()) {
      Keyboard.release(keys[i].keycode);
    }
  }
}
