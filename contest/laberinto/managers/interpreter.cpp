/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <nlehmann@dcc.uchile.cl> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Nicolás Lehmann
 * ----------------------------------------------------------------------------
 */

// If first line is 0 -> parse errors
// If first line is 1 -> no cumple condiciones
// If first line is 2 -> Cumple condiciones pero no recogió todos los objetos
// If first line is 3 -> Cumple condiciones y recogió todos los objetos :-)

#include <iostream>
#include <cstdio>
#include <istream>
#include <memory>
#include <fstream>
#include <algorithm>
#include <string>
#include <functional>
#include <unordered_map>
#include <stack>
#include <vector>
#include <boost/variant.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <cassert>
using namespace std;

void abort(const std::string &str) {
  // Finish with error
  printf("0\n");
  std::cout << str << "\n";
  exit(0);
}

void normalize(std::string &str) {
  uint i = 0;
  std::vector<char> norm;
  char c;
  while (i < str.size() and (c = str[i]) != '#') {
    // Remove space before : or ;
    if (norm.size() > 0 and (c == ':' or c == ';') and norm.back() == ' ')
      norm.pop_back();

    // If it is a space add it only if the last character was not already and
    // space
    if (not isspace(c))
      norm.push_back(c);
    else if (norm.size() > 0 and norm.back() != ' ')
      norm.push_back(' ');

    // Add a space after :
    if (c == ':')
      norm.push_back(' ');
    i++;
  }
  // We could have a space at the end.
  if (norm.size() > 0 and norm.back() == ' ') norm.pop_back();
  norm.push_back('\0');
  str = std::string(norm.data());
}

// enum Token {MV_RIGHT, MV_,LEFT, TAKE, DROP,
//             LOOP, POOL,
//             BRD_RIGHT, BRD_LEFT, HAS_PEBB, NO_PEBB,
//             BLANK, UNKW_CMD};

enum Token {
  FORWARD, TURN_LEFT, TURN_RIGHT,
  IF_FORWARD, IF_LEFT, IF_RIGHT, ELSE, ENDIF,
  LOOP, POOL,
  BLANK, UNKW_CMD
};

enum Cond {
  PATH_FORWARD,
  PATH_LEFT,
  PATH_RIGHT
};

struct Forward {};
struct TurnLeft {};
struct TurnRight {};
struct If;
struct Else {};
struct EndIf {};
struct Loop;
struct Pool {};

typedef boost::variant<
  Forward,
  TurnLeft,
  TurnRight,
  If,
  Loop
> Command;

struct Loop {
  std::vector<Command> commands;
  Loop(std::vector<Command> &&cmds) : commands(std::move(cmds)) {}
};

struct If {
  Cond cond;
  vector<Command> then_exprs;
  vector<Command> else_exprs;
  If(Cond c):
    cond(c),
    then_exprs(vector<Command>()),
    else_exprs(vector<Command>()) {}
  If(Cond c, vector<Command> &&te, vector<Command> &&ee):
    cond(c),
    then_exprs(std::move(te)),
    else_exprs(std::move(ee)) {}
};

struct Simulator {
  uint posx;
  uint posy;
  int dirx;
  int diry;
  int objects;
  vector<vector<int>> grid;
  Simulator(vector<vector<int> > &&grid, uint x, uint y, int dx, int dy,
            int o)
    : posx(x), posy(y), dirx(dx), diry(dy), objects(o),
      grid(std::move(grid))  {}
  void simulate(const std::vector<Command> &cmds);

  void forward() {
    if (checkCond(PATH_FORWARD)) {
      posx += dirx;
      posy += diry;
    }
    if (grid[posx][posy] == 'o') {
      objects--;
      grid[posx][posy] = ' ';
    }
  }

  void turnLeft() {
    if (posx == 0 and posy == 1) {
      posx = -1;
      posy = 0;
    }
    else if (posx == -1 and posy == 0) {
      posx = 0;
      posy = -1;
    }
    else if (posx == 0 and posy == -1) {
      posx = 1;
      posy = 0;
    }
    else if (posx == 1 and posy == 0) {
      posx = 0;
      posy = 1;
    }
  }

  void turnRight() {
    if (posx == 0 and posy == 1) {
      posx = 1;
      posy = 0;
    }
    else if (posx == 1 and posy == 0) {
      posx = 0;
      posy = -1;
    }
    else if (posx == 0 and posy == -1) {
      posx = -1;
      posy = 0;
    }
    else if (posx == -1 and posy == 0) {
      posx = 0;
      posy = 1;
    }
  }

  bool checkCond(Cond c) {
    switch (c) {
    case PATH_FORWARD:
      return grid[posx+dirx][posy+diry] != '*';
    case PATH_LEFT:
      return grid[posx-diry][posy+dirx] != '*';
    case PATH_RIGHT:
      return grid[posx+diry][posy-diry] != '*';
    }
  }

  bool checkFinish() {
    return objects == 0;
  }
};


struct Break {};

class do_cmd : public boost::static_visitor<void> {
 private:
  Simulator *sim;
 public:
  do_cmd(Simulator *sim) : sim(sim) {}

  void operator()(const Forward &) const {
    sim->forward();
    if (sim->checkFinish())
      throw Break();
  }

  void operator()(const TurnLeft &) const {
    sim->turnLeft();
  }

  void operator()(const TurnRight &) const {
    sim->turnRight();
  }

  void operator()(const If &e) const {
    if (sim->checkCond(e.cond))
      for (auto cmd : e.then_exprs)
        boost::apply_visitor(do_cmd(sim), cmd);
    else
      for (auto cmd : e.else_exprs)
        boost::apply_visitor(do_cmd(sim), cmd);
  }

  void operator()(const Loop &loop) const {
    while (true)
      for (auto cmd : loop.commands)
        boost::apply_visitor(do_cmd(sim), cmd);
  }
};

void Simulator::simulate(const std::vector<Command> &cmds) {
  for (auto cmd : cmds)
    try {
      boost::apply_visitor(do_cmd(this), cmd);
    } catch (Break) {}
}

struct lexer {
  std::unordered_map<std::string, Token> dict;
  lexer() {
    dict["avanzar"] = FORWARD;
    dict["girar izquierda"] = TURN_LEFT;
    dict["girar derecha"] = TURN_RIGHT;
    dict["si hay camino adelante:"] = IF_FORWARD;
    dict["si hay camino izquierda:"] = IF_LEFT;
    dict["si hay camino derecha:"] = IF_RIGHT;
    dict["else:"] = ELSE;
    dict["fin si;"] = ENDIF;
    dict["repetir:"] = LOOP;
    dict["fin repetir;"] = POOL;
    dict[""] = BLANK;
  }
  Token operator()(const std::string &str) {
    if (not dict.count(str))
      return UNKW_CMD;
    return dict[str];
  }
} Lexer;

Command tok2cmd(Token tok) {
  switch (tok) {
  case FORWARD: return Forward();
  case TURN_LEFT: return TurnLeft();
  case TURN_RIGHT: return TurnRight();
  default:
    abort("Unexpected token\n");
    exit(0);
  }
}

int nloop = 0;
int nifforward = 0;
int nifleft = 0;
int nifright = 0;
int nforward = 0;

std::vector<Command> parse(std::istream *lines) {
  std::string line;
  int i = 1;
  std::stack<pair<Token, std::vector<Command> > > frames;
  frames.push({UNKW_CMD, std::vector<Command>()});
  while (std::getline(*lines, line)) {
    normalize(line);
    Token tok = Lexer(line);

    if (tok == LOOP)
      nloop++;
    if (tok == IF_FORWARD)
      nifforward++;
    if (tok == IF_LEFT)
      nifleft++;
    if (tok == IF_RIGHT)
      nifright++;
    if (tok == FORWARD)
      nforward++;

    if (tok == BLANK)
      continue;
    if (tok == UNKW_CMD)
      abort("Error en línea " + std::to_string(i) + ": Comando desconocido: " +
            "`" + line + "`");
    if (tok == LOOP or tok == IF_FORWARD or tok == IF_LEFT or tok == IF_RIGHT) {
      frames.push({tok, std::vector<Command>()});
    } else if (tok == POOL) {
      if (frames.size() == 1 or frames.top().first != LOOP) {
        abort("Error en línea " + std::to_string(i) + ": No se esperaba una "
              "instrucción `fin repetir;`. Revisa que las instrucciones "
              "condicionales y de repetir estén bien anidadas.\n");
      }
      std::vector<Command> frame(std::move(frames.top().second));
      frames.pop();
      frames.top().second.push_back(Loop(std::move(frame)));
    } else if (tok == ELSE) {
      Token match_tok = frames.top().first;
      if (frames.size() == 1 or (match_tok != IF_LEFT and
                                 match_tok != IF_RIGHT and
                                 match_tok != IF_LEFT)) {
        abort("Error en línea " + std::to_string(i) + ": No se esperaba una "
              "instrucción 'sino:`. Revisa que las instrucciones "
              "condicionales y de repetir estén bien anidadas.\n");
      }
      frames.push({match_tok, std::vector<Command>()});
    } else if (tok == ENDIF) {
      Token match_tok = frames.top().first;
      if (frames.size() == 1 or (match_tok != IF_LEFT and
                                 match_tok != IF_RIGHT and
                                 match_tok != IF_LEFT)) {
        abort("Error en línea " + std::to_string(i) + ": No se esperaba una "
              "instrucción 'fin si;`. Revisa que las instrucciones "
              "condicionales y de repetir estén bien anidadas.\n");
      }
      std::vector<Command> else_frame(std::move(frames.top().second));
      frames.pop();
      std::vector<Command> then_frame(std::move(frames.top().second));
      frames.pop();
      Cond c = PATH_FORWARD;
      switch (match_tok) {
      case IF_FORWARD: c = PATH_FORWARD; break;
      case IF_LEFT: c = PATH_LEFT; break;
      case IF_RIGHT: c = PATH_RIGHT; break;
      default:
        abort("Unexpected match token\n");
        exit(0);
      }
      frames.top().second.push_back(If(c,
                                       std::move(then_frame),
                                       std::move(else_frame)));
    } else {
      frames.top().second.push_back(tok2cmd(tok));
    }
    i++;
  }
  if (frames.size() != 1)
    abort("Error en línea " + std::to_string(i) + ": Hay instrucciones `repetir`"
          " sin cerrar");
  return std::move(frames.top().second);
}

int main(int argc, char* argv[]) {
  if (argc < 2)
    abort("Usage: " + std::string(argv[0]) + " program_file");

  std::ifstream program_file(argv[1], std::ios::in);
  auto cmds = parse(&program_file);

  int N, M;
  int subtask;
  scanf("%d %d %d", &subtask, &N, &M);

  if (subtask == 2 and (nifleft > 0 or nifright > 0 or nforward > 3)) {
    printf("1\n");
    printf("Tu respuesta no cumple las restricciones de la subtarea. Haz"
           " usado %d veces la condición `hay camino izquierda`, %d veces la"
           " condición `hay camino derecha` y %d veces la instrucción"
           "`avanzar`.", nifleft, nifright, nforward);
    exit(0);
  }

  if (subtask == 3 and (nloop > 1 or nforward > 5)){
    printf("1\n");
    printf("Tu respuesta no cumple las restricciones de la subtarea. Haz"
           " usado %d veces la instrucción `repetir` y %d veces"
           " `avanzar`.", nloop, nforward);
    exit(0);
  }

  std::vector<vector<int> > grid(N+2, vector<int>(M, '*'));

  int objects = 0;
  char c;
  uint posx = 0;
  uint posy = 0;
  int dirx = 0;
  int diry = 0;
  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= M; ++j) {
      scanf("%c", &c);
      grid[i][j] = c;
      if (c == 'o')
        objects++;
      if (c == '<' or c == '>' or c == '^' or c == 'v') {
        posx = i;
        posy = j;
      }
      if (c == '<') {
        dirx = -1;
        diry = 0;
      }
      if (c == '^') {
        dirx = 0;
        diry = 1;
      }
      if (c == '>') {
        dirx = 1;
        diry = 0;
      }
      if (c == 'v') {
        dirx = 0;
        diry = -1;
      }
    }
    // Read newline
    scanf("%c", &c);
  }

  Simulator sim(std::move(grid), posx, posy, dirx, diry, objects);
  sim.simulate(cmds);

  if (sim.objects > 0)
    printf("2\n");
  else
    printf("3\n");
  return 0;
}
