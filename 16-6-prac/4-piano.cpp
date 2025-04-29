#include <iostream>
#include <string>
#include <limits>

enum note
{
    DO = 1,
    RE = 2,
    MI = 4,
    FA = 8,
    SOL = 16,
    LA = 32,
    SI = 64
};

std::string notes_str (int chord_mask) {
  std::string note;
  if (chord_mask & DO)  note = "DO ";
  if (chord_mask & RE)  note = "RE ";
  if (chord_mask & MI)  note = "MI ";
  if (chord_mask & FA)  note = "FA ";
  if (chord_mask & SOL) note = "SOL ";
  if (chord_mask & LA)  note = "LA ";
  if (chord_mask & SI)  note = "SI ";
  return note;
}

int main() {
  while(true){
    std::string notes;
    std::string input;
    std::cout << "Input chords: ";
    std::cin >> input;

    bool success = true;
    int note_index = 0;
    int chord_mask = 0;

    for (int i = 0; i < input.length(); i++){
      char chord = input[i];
      if (chord < '1' || chord > '7') { 
        std::cerr << "Out of range\n\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        success = false;
        break;
      }
      note_index = chord - '1';
      chord_mask |= (1 << note_index);
      notes += notes_str(chord_mask);
      chord_mask = 0;
    }
    if (!success) continue;
    std::cout << "Notes: " << notes << "\n\n";
  }
}