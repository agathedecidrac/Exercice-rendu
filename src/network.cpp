#include "network.h"
#include "random.h"
#include <string>
#include <iostream>
#include <map>

void Network::resize(const size_t& i){
  values.clear();
  values.resize(i);
  RNG.normal(values);
}

bool Network::add_link(const size_t& a, const size_t& b) {
  if (a!=b and a<values.size() and b<values.size() and a>=0 and b>=0){
    std::vector<size_t> voisins (neighbors(a));
    for (auto v: voisins){
      if (v==b)return false;
    }
    links.insert({a,b});
    links.insert({b,a});
    return true;
  } else {return false;}
}


size_t Network::random_connect(const double& d){
    links.clear();
    size_t nbr;
    size_t t(0);
    for (size_t i(0); i<values.size(); ++i){
      nbr=RNG.poisson(d);
      if (nbr>values.size()-1) nbr=values.size()-1;
      for (size_t j(0); j<nbr; ++j){
        while (not add_link(i,RNG.uniform_double(0,values.size()-1))){
        }; ++t;
      }
    }return t;
}

size_t Network::set_values(const std::vector<double>& valeurs){
  size_t taille(valeurs.size());
  //links.clear();
  if (taille<values.size()){
    for(unsigned int i(0);i<taille;++i){
      values[i]=(valeurs[i]);
    }
    return valeurs.size();
  } else {
    for(unsigned int i(0);i<values.size();++i){
      values[i]=(valeurs[i]);
    }
  }
  return values.size();
}

size_t Network::size() const{
  return values.size();
}

size_t Network::degree(const size_t & n) const{
  return links.count(n);
}

double Network::value(const size_t & n) const{
  if (values.size()>n) {return values[n];
  } else {throw std::string ("cet indice de value n'est pas dans values");}
}

std::vector<double> Network::sorted_values() const{
  std::vector<double> valeurs (values);
  std::sort(valeurs.begin(), valeurs.end());
  std::reverse(valeurs.begin(), valeurs.end());
  return valeurs;
}

std::vector<size_t> Network::neighbors(const size_t& t) const{
  std::vector<size_t> voisins;
    for (auto elements: links){
      if (elements.first==t){
        voisins.push_back(elements.second);
      }
  } return voisins;//else {throw std::string ("cet indice de value n'est pas dans values");}
}
