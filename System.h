#pragma once

#include "Particle.h"

#include <string>
#include <vector>

class System;

std::istream &operator>>(std::istream &is, System &s);
std::ostream &operator<<(std::ostream &os, System &s);

class System {
  friend std::istream &operator>>(std::istream &, System &);
  friend std::ostream &operator<<(std::ostream &, System &);

public:
  std::string description;

  typedef std::vector<Particle> Subsystem;
  Subsystem hard;
  Subsystem complete;

  typedef std::vector<std::vector<size_t>> Index;
  bool build_index();
  const Index &get_hard_index();
  const Index &get_complete_index();

  bool build_information();

  size_t prolong = 0;

private:
  Index hard_index;
  Index complete_index;
  size_t no_width = 0;
  size_t name_width = 0;
  size_t e_width = 0;
  size_t phase_width = 0;
  bool hard_index_built = false;
  bool complete_index_built = false;
  bool information_built = false;

  static bool build_index(Index &, Subsystem &);
  bool build_information(const Index &, Subsystem &);
  bool preprocess();
  static bool preprocess(Subsystem &);
  static size_t get_phase(size_t no, Subsystem &);
  std::ostream &
    print(std::ostream &, const Index &, const Subsystem &) const;
  std::ostream &
    print_all(std::ostream &, const Index &, Subsystem) const;
};
