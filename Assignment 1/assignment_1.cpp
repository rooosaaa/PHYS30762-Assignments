// PHYS30762 - Assignment 1
// Author: Rosa Roberts 
// Student ID: 11016395
// Date: 02-02-2025
// Program to compute transition energy using the Bohr formula

#include<iostream>
#include<iomanip>
#include <limits>
#include<cmath>

// Constants
const double RYDBERG_EV = 13.6; // Rydberg constant (eV)
const double ENERGY_CONVERSION = 1.60218e-19; // eV to Joules

double photon_energy(int Z, int n_i, int n_f)
{
  // Computes photon energy in eV
  double energy_ev = RYDBERG_EV * pow(Z, 2) * (1.0/(pow(n_f, 2)) - 1.0/(pow(n_i, 2)));
  return energy_ev;
}

double convert_energy(double photon_energy)
{
  // Converts energy from eV to Joules
  return photon_energy * ENERGY_CONVERSION;
}

bool check_integer(std::string& input)
{
  // Checks if input string is a valid integer
  for (char c: input)
  {
    if (!isdigit(c)) return false; 
  }
  return true;
}

bool check_whitespace(std::string& input)
{
  // Checks if input string contains whitespace
  for (char c: input)
  {
    if (isspace(c)) return true;
  }
  return false;
}

int get_positive_integer_input(const std::string& prompt)
{
  // Gets positive integer input from user
  std::string input_str;
  int input = 0;
  std::cout << prompt;
  std::getline(std::cin, input_str);  // Use getline to read the whole line

  while (check_whitespace(input_str) || !check_integer(input_str) || std::stoi(input_str) <= 0)
  {
    std::cout << "Invalid input. Please enter a positive integer without symbols or whitespace: ";
    std::getline(std::cin, input_str);
  }
  input = std::stoi(input_str);
  return input;
}

int main()
{
  std::string repeat{"y"};
  while(repeat == "y")
  {
    // Declaring variables
    int atomic_number; 
    int n_initial, n_final; 
    std::string energy_unit;

    atomic_number = get_positive_integer_input("Enter atomic number: ");
    n_initial = get_positive_integer_input("Enter initial quantum number: ");
    n_final =  get_positive_integer_input("Enter final quantum number: ");

    // Ensure n_initial > n_final
    while(n_initial <= n_final)
    {
      std::cout << "Invalid input. Please enter initial quantum number " 
                << "greater than final quantum number." << std::endl;
      n_initial = get_positive_integer_input("Enter initial quantum number: ");
      n_final =  get_positive_integer_input("Enter final quantum number: ");
    }

    // Ask user to enter energy unit
    std::cout << "Enter desired units ('J' or 'eV'): ";
    std::cin >> energy_unit;
    while (energy_unit != "J" && energy_unit != "eV")
    {
    std::cout << "Invalid input. Please enter 'J' or 'eV': ";
    std::cin >> energy_unit;
    }

    // Compute and display photon energy
    if (energy_unit == "J")
    {
      double transition_energy = convert_energy(photon_energy(atomic_number, n_initial, n_final));
      std::cout << "Transition energy: " << std::setprecision(3) << transition_energy << " J" << std::endl;
    }
    else
    {
      double transition_energy = photon_energy(atomic_number, n_initial, n_final);
      std::cout << "Transition energy: " << std::setprecision(3) << transition_energy << " eV" << std::endl;
    }

    // Ask if user wants to repeat and stop if the answer is no
    std::cout << "Would you like to repeat the calculation? (y/n): ";
    std::cin >> repeat;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear the buffer
    while (repeat != "n" && repeat != "y")
    {
    std::cout << "Invalid input. Please enter 'n' or 'y': ";
    std::cin >> repeat;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear the buffer
    }
  } 
  std::cout << "----------------------------" << std::endl;
  std::cout << "Program terminated. Goodbye!" << std::endl;
  std::cout << "----------------------------" << std::endl;
  return 0;
}
