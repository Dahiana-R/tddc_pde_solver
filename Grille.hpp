#ifndef GRILLE_HPP
#define GRILLE_HPP

#include <vector>

namespace dauphine
{//  Définition du mesh Borne sup et inf du stock, Timenumber et stocknumber = Nombre de "pas", le vecteur sert a rien pour l'instant, plus tard surement pour définir les boundaries
//dx et dt correspondent à la taille des step qui sont calculés. Peut être tout définir sous forme de vecteur...?
	//Plein de variables inutiles, je me suis pris la tête, enlevé Stockmin, Time Number certainement...
	class Grille {
	public:
		Grille(double Time, double StockMax, double StockMin, double dt, double dx);
		std::vector<double> getStockVector() const;
		std::vector<double> getTimeVector() const;
		double getdt() const;
		double getTimeNumber() const;
		double GetTailleStock() const;
		double getdx() const;
		~Grille();

	private:
		double Time;
		double StockMax;
		size_t TimeNumber;
		size_t StockNumber;
		double dt;
		double dx;
		std::vector<double> StockVector;
	};
}

#endif