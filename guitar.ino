// defined by instrument and hardware
#define TONALITIES 6
#define HARMONIES 7
#define STRNGS 6
#define FRETS 3
// fingering chart ("Grifftabelle")
#define EMPTY       {0,0,0,0,0,0}
#define C_MAJ       {0,3,2,0,1,0}
#define D_MAJ       {0,0,0,2,3,2}     // just play strings 2-6
#define E_MAJ       {0,2,2,1,0,0}
#define F_MAJ       {1,3,3,2,1,1}
#define G_MAJ       {3,2,0,0,0,3}
#define A_MAJ       {0,0,2,2,2,0}
#define B_MAJ       {0,2,1,2,0,2}     // same as B_MAJ_7
#define B_FLAT_MAJ  {1,1,3,3,3,1}
#define C_MAJ_7     {0,3,2,3,1,0}
#define D_MAJ_7     {0,0,0,2,1,2}     // just play strings 2-6
#define E_MAJ_7     {0,2,2,1,3,0}
#define F_MAJ_7     {1,3,1,2,1,1}
#define G_MAJ_7     {3,2,0,0,0,1}
#define A_MAJ_7     {0,0,2,2,2,3}
#define B_MAJ_7     {0,2,1,2,0,2}
#define C_MIN       {0,0,0,0,0,0}     // impossible on 3 frets
#define D_MIN       {0,0,0,2,3,1}     // just play strings 2-6
#define E_MIN       {0,2,2,0,0,0}
#define F_MIN       {1,3,3,1,1,1}
#define G_MIN       {3,0,0,3,3,3}     // incomplete: just play strings 1,4,5,6
#define A_MIN       {0,0,2,2,1,0}
#define B_MIN       {0,0,0,0,0,0}     // impossible on 3 frets

// pin configuration
const int pin_test = 16;
const int pin_tonality[TONALITIES] = {2,3,4,5,6,7};   // C,D,E,F,G,A
const int pin_harmony[HARMONIES] = {9,10,11,12,13,14,15};   // Tonika, Subdominante, Dominante, Dominante Septime, Mollparallele, Subdominante Moll, NN
const int pin_magnet[FRETS][STRNGS] = {{22,24,26,28,30,32},{34,36,38,40,42,44},{46,48,50,52,51,53}};

// button configuration
const byte chords[TONALITIES][HARMONIES][STRNGS] = {
  {C_MAJ,F_MAJ,G_MAJ,G_MAJ_7,A_MIN,D_MIN,EMPTY},
  {D_MAJ,G_MAJ,A_MAJ,A_MAJ_7,E_MIN,B_MIN,EMPTY},
  {E_MAJ,A_MAJ,B_MAJ,B_MAJ_7,EMPTY,EMPTY,EMPTY},
  {F_MAJ,B_FLAT_MAJ,C_MAJ,C_MAJ_7,D_MIN,G_MIN,EMPTY},
  {G_MAJ,C_MAJ,D_MAJ,D_MAJ_7,A_MIN,E_MIN,EMPTY},
  {A_MAJ,D_MAJ,E_MAJ,E_MAJ_7,EMPTY,EMPTY,EMPTY}
};

void setup() {
  pinMode(pin_test,INPUT_PULLUP);
  for (int tonality=0; tonality<TONALITIES; tonality++)
    pinMode(pin_tonality[tonality],INPUT_PULLUP);
  for (int harmony=0; harmony<HARMONIES; harmony++)
    pinMode(pin_harmony[harmony],INPUT_PULLUP);
  for (int fret=0; fret<FRETS; fret++)
    for (int strng=0; strng<STRNGS; strng++)
      pinMode(pin_magnet[fret][strng],OUTPUT);
}

void test_routine() {
  // release all magnets
  for (int fret=0; fret<FRETS; fret++)
    for (int strng=0; strng<STRNGS; strng++)
      digitalWrite(pin_magnet[fret][strng],LOW);
  // apply each magnet for 0.5sec
  for (int fret=0; fret<FRETS; fret++)
    for (int strng=0; strng<STRNGS; strng++) {
      digitalWrite(pin_magnet[fret][strng],HIGH);
      delay(500);
      digitalWrite(pin_magnet[fret][strng],LOW);
    }
}

void loop() {
  if (digitalRead(pin_test)==LOW)
    test_routine();
  else {
    byte chord[STRNGS] = EMPTY;
    // read input pins and select chord
    for (int tonality=0; tonality<TONALITIES; tonality++)
      if (digitalRead(pin_tonality[tonality])==LOW)
        for (int harmony=0; harmony<HARMONIES; harmony++)
          if (digitalRead(pin_harmony[harmony])==LOW)
            for (int strng=0; strng<STRNGS; strng++)
              chord[strng]=chords[tonality][harmony][strng];
    // drive magnets to play selected chord
    for (int fret=0; fret<FRETS; fret++)
      for (int strng=0; strng<STRNGS; strng++)
        digitalWrite(pin_magnet[fret][strng],chord[strng]==fret+1);
  }
}