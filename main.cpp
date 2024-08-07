#include <set>
#include <iostream>
#include <fstream>
#include <ctime>

#define SET_PITANJA "set_pitanja.txt"
#define SET_ODGOVORENIH_PITANJA "set_odgovorenih_pitanja.txt"
#define SET_NEODGOVORENIH_PITANJA "set_neodgovorenih_pitanja.txt"

void backup_txt_file_to_destination(std::string og_file_path, std::string new_file_path) {
    std::ifstream og_file(og_file_path);
    std::ofstream new_file(new_file_path);
    int br;
    while (!og_file.eof())
    {
        og_file >> br;
        new_file << br << " ";
    }
    og_file.close();
    new_file.close();
    
}

/**
 * Funkcija popunjava set i txt fajl nizom brojeva od 1 do br_pitanja-1
 */
std::set<int> pitanja_init(int br_pitanja, std::string txt_fajl) {
    std::set<int> pitanja;
    std::ofstream sva_pitanja(txt_fajl);
    for(int i=1;i<br_pitanja;i++) {
        pitanja.insert(i);
        sva_pitanja << i << " ";
    }
    sva_pitanja.close();
    return pitanja;
}

/**
 * Nije testirano
 */
std::set<int> init_set_from_txt(std::string txt_fajl) {
    std::set<int> pitanja;
    std::ifstream ostala_pitanja(txt_fajl);
    int br;
    while (!ostala_pitanja.eof()) {
        ostala_pitanja >> br;
        pitanja.insert(br);
    }
    ostala_pitanja.close();
    return pitanja;
}

void init_txt_from_set(const std::set<int> &pitanja, std::string txt_fajl) {
    std::ofstream sva_pitanja(txt_fajl);
    std::set<int>::iterator it;
    for(it=pitanja.begin(); it != pitanja.end();++it) {
        //pitanja.insert(i);
        sva_pitanja << *it << " ";
    }
    sva_pitanja.close();
}

void quick_save_int_in_txt(int br, std::string txt_fajl) {
    std::ofstream sva_pitanja(txt_fajl, std::ios_base::app);
    sva_pitanja << br << " ";
    sva_pitanja.close();
}

int main() {
    
    std::set<int> sva_pitanja, odgovorena_pitanja;
    sva_pitanja = pitanja_init(170, SET_PITANJA);
    odgovorena_pitanja = init_set_from_txt(SET_ODGOVORENIH_PITANJA);
    std::cout << sva_pitanja.size() << "\n";
    std::cout << odgovorena_pitanja.size() << "\n";

    int izbor = 0;
    while (izbor != -1)
    {
        std::cout << "\nKoje Vas pitanje zanima? (-1 izlazi iz programa i spasava podatke)\n:";
        std::cin>>izbor;
        if(sva_pitanja.count(izbor)==1) {
            if (odgovorena_pitanja.count(izbor)==1) {
                std::cout << "Odgovor postoji\n";
            } else {
                std::cout << "Odgovor nepostoji\nDodajem ga u set odgovorenih...\n";
                odgovorena_pitanja.insert(izbor);
                quick_save_int_in_txt(izbor, SET_ODGOVORENIH_PITANJA);
            }
        } else if(izbor != -1) {
            std::cout << "Pitanje " << izbor << " nepostoji\n";
        } /*else {
            std::cout << "Ti si kralj\n";
            return 76;
        }*/
        
    }
    //odgovorena_pitanja.erase(-1);
    init_txt_from_set(odgovorena_pitanja, SET_ODGOVORENIH_PITANJA);
    //Backup
    init_txt_from_set(odgovorena_pitanja, std::to_string(time(NULL)));
    std::cout << "Bye.\n";

    
    return 0;
}