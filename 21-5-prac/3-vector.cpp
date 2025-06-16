#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

struct vec {
  double x = 0;
  double y = 0;
};

bool invalid_cin (){

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  if (std::cin.fail()){
    std::cerr << "\n**ERROR**\n\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return true;
  }

  return false;
}

void coords_input (std::string& code, vec& vec2){

  std::string coords;

  while(true){
    std::cout << code;
    std::cout << "Input coords(x y): ";
    getline(std::cin, coords);
    std::stringstream coords_str(coords);
    coords_str >> vec2.x >> vec2.y;

    if (coords_str.fail()){
      std::cerr << "\n**ERROR**\n\n";
      continue;
    }

    break;
  }

}

void result_output(vec& res_vec){

  std::cout << "\n**RESULT**\n\n";
  std::cout << "vec(" << res_vec.x << ", " << res_vec.y << ")" << std::endl;
  std::cout << "x = " << res_vec.x << std::endl;
  std::cout << "y = " << res_vec.y << std::endl << std::endl;

}

void vec_add (vec& vec2, vec& res_vec, std::string& code){

  std::vector<vec> v_add;
  
  for(int i = 0; i < 2; i++){

    code = "(AV";
    code.append(std::to_string(i+1)).append(") ");
    coords_input(code, vec2);

    v_add.push_back(vec2);

  }

  res_vec.x = v_add[0].x + v_add[1].x;
  res_vec.y = v_add[0].y + v_add[1].y;

}

void vec_subtract (vec& vec2, vec& res_vec, std::string& code){

  std::vector<vec> v_subtract;

  for(int i = 0; i < 2; i++){
    
    code = "(AV";
    code.append(std::to_string(i+1)).append(") ");
    coords_input(code, vec2);

    v_subtract.push_back(vec2);

  }

  res_vec.x = v_subtract[0].x - v_subtract[1].x;
  res_vec.y = v_subtract[0].y - v_subtract[1].y;

}

void vec_scale (vec& vec2, vec& res_vec, std::string& code){

  coords_input(code, vec2);

  double number = 0;

  while(true){
    std::cout << "(ScN) Input number: ";
    std::cin >> number;

    if(invalid_cin())
      continue;

    break;

  }

  res_vec.x = vec2.x * number;
  res_vec.y = vec2.y * number;

}

double vec_length (vec& vec2, vec& res_vec, std::string& code){
  
  coords_input(code, vec2);

  double v_length = 0;
  v_length = std::round(std::sqrt(std::pow(vec2.x, 2) + std::pow(vec2.y, 2)) * 100) / 100;

  return v_length;

}

double vec_normalize (vec& vec2, vec& res_vec, std::string& code){

  double v_length = vec_length(vec2, res_vec, code);

  if (v_length == 0){
    std::cerr << "\n**Error: Vector length is null**\n\n";
    return 0;
  }
  
  res_vec.x = vec2.x / v_length;
  res_vec.y = vec2.y / v_length;
    
  return v_length;
}

int main(){

  vec vec2;
  vec res_vec;
  std::string code;

  std::cout << "**Command list**\n\n";
  printf("add\nsubtract\nscale\nlength\nnormalize\n\n");

  while(true){

    std::string cmd;
    std::cout << "Input command: ";
    std::cin >> cmd;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (cmd == "add"){
      code = "(AV";
      vec_add(vec2, res_vec, code);
      result_output(res_vec);
    }
    else if (cmd == "subtract"){
      code = "(SubV";
      vec_subtract(vec2, res_vec, code);
      result_output(res_vec);
    }
    else if (cmd == "scale"){
      code = "(ScV) ";
      vec_scale(vec2, res_vec, code);
      result_output(res_vec);
    }
    else if (cmd == "length"){
      code = "(LV) ";
      double v_length = vec_length(vec2, res_vec, code);
      std::cout << "\n**RESULT**\n\n";
      std::cout << "Vector length (" << vec2.x << ", " << vec2.y << ") = " << v_length << std::endl << std::endl;
    }
    else if (cmd == "normalize"){
      code = "(NV) ";
      double v_length = vec_normalize(vec2, res_vec, code);
      if (v_length == 0)
        continue;
      std::cout << "\n**RESULT**\n\n";
      std::cout << "Vector normalize (" << vec2.x << ", " << vec2.y << ") = " << "(" << res_vec.x << ", " << res_vec.y << ")" << std::endl << std::endl;
    }
    else 
      std::cerr << "\n**Unknown command**\n\n";

  }

}