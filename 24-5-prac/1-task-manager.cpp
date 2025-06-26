#include <iostream>
#include <ctime>
#include <iomanip>
#include <string>
#include <limits>
#include <vector>

void new_task(std::pair<std::string, std::tm>& task){

  std::string task_in;
  while (true){
    std::cout << "Input task: ";
    getline(std::cin, task_in);

    if (!task_in.empty()) {
      if (task_in != task.first){
        task.first = task_in;
        std::cout << std::endl;
        return;
      }
      else
        std::cerr << "\n**Task in process**\n\n";
    }
    else
      std::cerr << "\n**Input anything**\n\n";
  }
}

void time_update(std::pair<std::string, std::tm>& task){

  std::time_t t = std::time(nullptr);
  std::tm local = *std::localtime(&t);
  task.second = local;

}

int main(){

  std::pair<std::string, std::tm> task;
  std::vector<std::pair<std::string, std::tm>> task_history;
  std::string cmd;
  
  while(true){

    std::cout << "Input command: ";
    std::cin >> cmd;

    if (!cmd.empty()){

      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      if (cmd == "begin"){
        std::string end;
        if (task_history.size() != 0 && task_history.size() % 2 != 0){

          std::time_t t1 = mktime(&task.second);
          std::time_t t2 = mktime(&task_history.back().second);

          if (t1 == t2){

            time_update(task);
            task_history.push_back(task);
            // std::cout << "\nTask: " << task.first << "\n";
            // std::cout << "Ended at: " << std::asctime(&task.second) << "\n";
            end = "Task: " + task.first + "\n" + "Ended at: " + std::asctime(&task.second) + "\n";

          }

        }
        new_task(task);
        time_update(task);
        task_history.push_back(task);
        std::cout << end;
        std::cout << "Task: " << task.first << std::endl;
        std::cout << "Started at: " << std::asctime(&task.second) << std::endl;
      }

      else if (cmd == "end")
        if (task_history.size() % 2 != 0){
          time_update(task);
          task_history.push_back(task);
          std::cout << "\nTask: " << task.first << std::endl;
          std::cout << "Ended at: " << std::asctime(&task.second) << std::endl;
        }
        else 
          std::cerr << "\n**No task in process**\n\n";

      else if (cmd == "status"){
        std::cout << std::endl;
        if (!task_history.empty()){
          if (task_history.size() % 2 == 0)
            for (int i = 1; i < task_history.size() - 1; i += 2){
              std::cout << "Task: " << task_history[i].first << std::endl;
              std::cout << "Started at: " << std::asctime(&task_history[i-1].second);
              std::cout << "Ended at: " << std::asctime(&task_history[i].second) << std::endl;
            }

          if (task_history.size() % 2 != 0){
            for (int i = 1; i < task_history.size() - 1; i += 2){
              std::cout << "Task: " << task_history[i].first << std::endl;
              std::cout << "Started at: " << std::asctime(&task_history[i-1].second);
              std::cout << "Ended at: " << std::asctime(&task_history[i].second) << std::endl;
            }
            // std::cout << "Task: " << task_history.back().first << std::endl;
            std::cout << "Started at: " << std::asctime(&task_history.back().second) << std::endl;
          }

        }
        else if (cmd == "exit") {
          std::cout << "\n**Exiting program**\n\n";
          break;   
        }
        else
          std::cerr << "\n**Task history is empty**\n\n";
      }

      else
        std::cerr << "\n**Unknown command**\n\n";

    } 
    else
      std::cerr << "\n**Input anything**\n\n";

  }

}