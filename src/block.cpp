#include "block.h"

block::block(bool visited, bool exit, bool light, bool hole, bool breeze) {
  this->visited = visited;
  this->exit = exit;
  this->light = light;
  this->hole = hole;
  this->breeze = breeze;
}

block::block() {}

block::~block() {}

void block::visit() { this->visited = true; this->ocuppied = true; }

void block::leave() { this->ocuppied = false; }

bool block::isAHole() { return this->hole; }

bool block::isExit() { return this->exit; }

bool block::thereIsBreeze() { return this->breeze; }

bool block::thereIsLight() { return this->light; }

bool block::wasVisited() { return this->visited; }

bool block::isOcuppied() { return this->ocuppied; }

bool block::isOrdinary() {
  return (!this->exit && !this->light && !this->hole && !this->breeze);
}
