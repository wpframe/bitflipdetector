# Bit Flip Detector

A simple C program to detect bit flips possibly caused by cosmic rays.

Allocates a gigabyte array and checks for bit flips. If a bit flip is found it prints the unix timestamp, test number, and location in the array.

It runs indefinitely until it receives a SIGINT.

[Wikipedia on Soft Errors (cosmic rays creating energetic neutrons and protons)](https://en.wikipedia.org/wiki/Soft_error#Cosmic_rays_creating_energetic_neutrons_and_protons)
