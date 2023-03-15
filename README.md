# GuitarWizard
My father has been playing the guitar for decades, when singing with friends and family, at the campfire and on many occasions and celebrations. Unfortunately, he lost three phalanges on his left hand during an accident some time ago, preventing him from playing any chord on a normal guitar. He tried to switch to a mirrored instrument, but this turned out to be impossible to learn for someone with >60 years of practice.

Since his left thumb and forefinger are still okay, he decided to design an electromechanic device allowing him to select a tonality and play the harmonies just by pushing a single button, while the strings are pushed down by solenoids and his right hand is doing the rhythm and picking part as before.

The design includes a solenoid module being attached to the neck between frets 1-3 with 18 solenoids (6 strings on 3 frets), and a control module based on an Arduino Mega 2560 board translating the button input into chords. The control program of the Arduino board consists of the definitions for the mechanic setup and the fingering table, constant arrays for assigning the Arduino pins and chords, and the subroutines for setup, test and loop.
