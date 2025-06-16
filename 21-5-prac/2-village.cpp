#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <limits>

enum plot_buildings{
  live_house_type,
  shed_type,
  garage_type,
  bathhouse_type
};

enum room_type {
  bedroom,
  kitchen,
  bathroom,
  kids_room,
  living_room
};

struct room {
  int square = 0;
  room_type r_type;
};

struct floor {
  int ceiling_height = 0;
  std::vector<room> rooms;
};

struct live_house {
  bool furnace_pipe = false;
  int square = 0;
  std::vector<floor> floors;
};

struct shed {
  int square = 0;
};

struct garage {
  int square = 0;
};

struct bathhouse {
  int square = 0;
  bool furnace_pipe = false;
};

struct plot {
  int id = 0;
  std::vector<live_house> house_plot;
  std::vector<shed> shed_plot;
  std::vector<garage> garage_plot;
  std::vector<bathhouse> bathhouse_plot;
};

struct village {
  std::vector<plot> plots;
};

bool invalid_cin(){

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  if (std::cin.fail()){
    std::cerr << "\n**ERROR**\n\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return true;
  }

}

int main() {
  room rm;
  village vlg;

  int plots_amount = 0;
  while(true){
    
    std::cout << "Input amount of plots: ";
    std::cin >> plots_amount;

    if (invalid_cin())
      continue;

    if (plots_amount <= 0){
      std::cerr << "\n**ERROR**\n\n";
      continue;
    }
    break;
  }

  int id = 0;

  while (id != plots_amount){
    plot cur_plot;

    ++id;
    cur_plot.id = id;

    std::cout << "\n**PLOT " << id << "**\n\n";

    int builds_amount = 0;
    while (true){
      printf("(P%d) ", id);
      std::cout << "Input amount of builds(1-4): ";
      std::cin >> builds_amount;
      if (invalid_cin())
        continue;
      
      if (builds_amount < 1 || builds_amount > 4){
        std::cerr << "\n**ERROR**\n\n";
        continue;
      }
      break;
    }

    int cur_build = 0;
    while (cur_build != builds_amount){
      ++cur_build;
      std::cout << "\n**PLOT " << id << " BUILD " << cur_build << "**\n\n";
      std::string build; 
      while(true){
        std::cout << "**List**\n\nlive_house\nshed\ngarage\nbathhouse\n\n";
        printf("(P%dB%d) ", id, cur_build);
        std::cout << "Input building type from list: ";
        std::cin >> build;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (build == "live_house"){
        live_house houseObj;

        while (true){
          printf("(P%dB%d) ", id, cur_build);
          std::cout << "Input live house square: ";
          std::cin >> houseObj.square;

          if (invalid_cin())
            continue;
          
          if (houseObj.square <= 0){
            std::cerr << "\n**ERROR**\n\n";
            continue;
          }
          break;
        }

        while(true){
          std::string furnace_pipe_availability;
          printf("(P%dB%d) ", id, cur_build);
          std::cout << "Input furnace with pipe availability(yes/no): ";
          std::cin >> furnace_pipe_availability;
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          if (furnace_pipe_availability == "yes")
            houseObj.furnace_pipe = true;
          else if (furnace_pipe_availability == "no");
          else {
            std::cerr << "\n**ERROR**\n\n";
            continue;
          }
          break;
        }

        int floors_amount;
        while (true){
          printf("(P%dB%d) ", id, cur_build);
          std::cout << "Input floors amount (1-3): ";
          std::cin >> floors_amount;
          if (invalid_cin())
            continue;
          
          if (floors_amount < 1 || floors_amount > 3){
            std::cerr << "\n**ERROR**\n\n";
            continue;
          }
          break;
        }

        int fl_ceiling_height = 0;

        while(true){
          printf("(P%dB%d) ", id, cur_build);
          std::cout << "Input ceiling height: ";
          std::cin >> fl_ceiling_height;
          if (invalid_cin())
            continue;

          if (fl_ceiling_height <= 0){
            std::cerr << "\n**ERROR**\n\n";
            continue;
          }
          break;
        }

        for (int i = 0; i < floors_amount; ++i){
          floor fl;
          fl.ceiling_height = fl_ceiling_height;
          int rooms_amount;
          while(true){
            printf("(P%dB%d) ", id, cur_build);
            std::cout << "Input floor " << i + 1 << " rooms amount(2-4): ";
            std::cin >> rooms_amount;
            if (invalid_cin())
              continue;
            
            if (rooms_amount < 2 || rooms_amount > 4){
              std::cerr << "\n**ERROR**\n\n";
              continue;
            }
            break;
          }

          int sum_rm_square = 0;

          for (int j = 0; j < rooms_amount; ++j){

            std::vector<std::string> r_types;

            while(true){
              printf("(P%dB%d) ", id, cur_build);
              std::cout << "Input floor " << i + 1 << "/" << floors_amount << " room " << j + 1 << "/" <<  rooms_amount << " square(free: "<< houseObj.square - sum_rm_square << "): ";
              std::cin >> rm.square;
              sum_rm_square += rm.square;
              if (invalid_cin())
                continue;

              if (rm.square <= 0 || sum_rm_square > houseObj.square || (j == rooms_amount - 1 && sum_rm_square != houseObj.square)){
                std::cerr << "\n**ERROR**\n\n";
                sum_rm_square -= rm.square;
                continue;
              }

              break;
            }

            while(true){
              std::cout << "\n**List**\n\nbedroom\nkitchen\nbathroom\nkids_room\nliving_room\n\n";
              std::string r_type_str;
              printf("(P%dB%d) ", id, cur_build);
              std::cout << "Input room " << j + 1 << " type from list: ";
              std::cin >> r_type_str;
              std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
              
              if (r_type_str == "bedroom"){
                rm.r_type = bedroom;
              }
              else if (r_type_str == "kitchen"){
                rm.r_type = kitchen;
              }
              else if (r_type_str == "bathroom"){
                rm.r_type = bathroom;
              }
              else if (r_type_str == "kids_room"){
                rm.r_type = kids_room;
              }
              else if (r_type_str == "living_room"){
                rm.r_type = living_room;
              }
              else {
                std::cerr << "\n**ERROR**\n\n";
                continue;
              }

              break;
            }

            fl.rooms.push_back(rm);

          }

          houseObj.floors.push_back(fl);

        }

        cur_plot.house_plot.push_back(houseObj);
        break;

      }

        else if (build == "shed"){
        shed shedObj;

        while (true){
          printf("(P%dB%d) ", id, cur_build);
          std::cout << "Input shed square: ";
          std::cin >> shedObj.square;
          if (invalid_cin())
            continue;
          
          if (shedObj.square <= 0){
            std::cerr << "\n**ERROR**\n\n";
            continue;
          }
          break;
        }

        cur_plot.shed_plot.push_back(shedObj);
        break;
      }
    
        else if (build == "garage"){
        garage garageObj;

        while (true){
          printf("(P%dB%d) ", id, cur_build);
          std::cout << "Input garage square: ";
          std::cin >> garageObj.square;
          if (invalid_cin())
            continue;

          if (garageObj.square <= 0){
            std::cerr << "\n**ERROR**\n\n";
            continue;
          }
          break;
        }

        cur_plot.garage_plot.push_back(garageObj);
        break;
      }
    
        else if (build == "bathhouse"){
        bathhouse bathhouseObj;

        while (true){
          printf("(P%dB%d) ", id, cur_build);
          std::cout << "Input bathhouse square: ";
          std::cin >> bathhouseObj.square;
          if (invalid_cin())
            continue;

          if (bathhouseObj.square <= 0){
            std::cerr << "\n**ERROR**\n\n";
            continue;
          }
          break;
        }

        while(true){
          printf("(P%dB%d) ", id, cur_build);
          std::string furnace_pipe_availability;
          std::cout << "Input furnace with pipe availability(yes/no): ";
          std::cin >> furnace_pipe_availability;
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          if (furnace_pipe_availability == "yes")
            bathhouseObj.furnace_pipe = true;
          else if (furnace_pipe_availability == "no");
          else {
            std::cerr << "\n**ERROR**\n\n";
            continue;
          }
          break;
        }

        cur_plot.bathhouse_plot.push_back(bathhouseObj);
        break;
      }
    
        else {
          std::cerr << "\n**Unknown type**\n\n";
          continue;
        }
      
      }

    }

    vlg.plots.push_back(cur_plot);

  }

  std::cout << "\n**MODEL**\n\n";

  for (int i = 0; i < vlg.plots.size(); ++i){

    std::cout << "**PLOT " << vlg.plots[i].id << "**\n\n";

    if (vlg.plots[i].house_plot.size() != 0){
      for(int j = 0; j < vlg.plots[i].house_plot.size(); ++j){

        std::cout << "**LIVE HOUSE " << j+1 << "**\n";
        std::cout << "Furnace pipe: " << std::boolalpha << vlg.plots[i].house_plot[j].furnace_pipe << std::endl;
        std::cout << "Square: " << vlg.plots[i].house_plot[j].square << std::endl;
        std::cout << "Floors: " << vlg.plots[i].house_plot[j].floors.size() << std::endl;
        for (int x = 0; x < vlg.plots[i].house_plot[j].floors.size(); ++x){
          std::cout << "Ceiling height: " << vlg.plots[i].house_plot[j].floors[x].ceiling_height << std::endl;
          std::cout << "Floor " << x+1 << " rooms: " << vlg.plots[i].house_plot[j].floors[x].rooms.size();
          for (int y = 0; y < vlg.plots[i].house_plot[j].floors[x].rooms.size(); ++y){
            std::cout << "\n\n\t**Room " << y+1 << "**\n\tSquare: " << vlg.plots[i].house_plot[j].floors[x].rooms[y].square << std::endl;
            std::string r_type;
            if (vlg.plots[i].house_plot[j].floors[x].rooms[y].r_type == 0)
              r_type = "bedroom";
            else if (vlg.plots[i].house_plot[j].floors[x].rooms[y].r_type == 1)
              r_type = "kitchen";
            else if (vlg.plots[i].house_plot[j].floors[x].rooms[y].r_type == 2)
              r_type = "bathroom";
            else if (vlg.plots[i].house_plot[j].floors[x].rooms[y].r_type == 3)
              r_type = "kids room";
            else if (vlg.plots[i].house_plot[j].floors[x].rooms[y].r_type == 4)
              r_type = "living room";
            std::cout << "\tType: " << r_type;
          }
        }
      }

      std::cout << std::endl << std::endl;

    }

    if (vlg.plots[i].shed_plot.size() != 0){
      for (int j = 0; j < vlg.plots[i].shed_plot.size(); ++j){
        std::cout << "**SHED " << j+1 << "**\n";
        std::cout << "Square: " << vlg.plots[i].shed_plot[j].square;
      }
      std::cout << std::endl << std::endl;
    }

    if (vlg.plots[i].garage_plot.size() != 0){
      for (int j = 0; j < vlg.plots[i].garage_plot.size(); ++j){
        std::cout << "**GARAGE " << j+1 << "**\n";
        std::cout << "Square: " << vlg.plots[i].garage_plot[j].square;
      }
      std::cout << std::endl << std::endl;
    }

    if (vlg.plots[i].bathhouse_plot.size() != 0){
      for (int j = 0; j < vlg.plots[i].bathhouse_plot.size(); ++j){
        std::cout << "**BATHHOUSE " << j+1 << "**\n";
        std::cout << "Square: " << vlg.plots[i].bathhouse_plot[j].square << std::endl;
        std::cout << "Furnace pipe: " << std::boolalpha << vlg.plots[i].bathhouse_plot[j].furnace_pipe;
      }
      std::cout << std::endl << std::endl;
    }
  }

}



