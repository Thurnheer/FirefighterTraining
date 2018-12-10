#include "init.hpp"
#include "fwunit.hpp"
#include "firebrigade.hpp"


void initFwBAH(FireBrigade& bah)
{
    bah.addUnit(FwUnit("Zug 1", "Zug 1"));
    bah.addUnit(FwUnit("Zug 2", "Zug 2"));
    bah.addUnit(FwUnit("Zug 3", "Zug 3"));
    bah.addUnit(FwUnit("Kommando Zug", "K-Zug"));

    bah.addUnit(FwUnit("Maschinisten A", "MD A"));
    bah.addUnit(FwUnit("Maschinisten B", "MD B"));
    bah.addUnit(FwUnit("Maschinisten C", "MD C"));
    bah.addUnit(FwUnit("Hubretter", "HRB"));

    bah.addUnit(FwUnit("Atemschutz A", "AS A"));
    bah.addUnit(FwUnit("Atemschutz B", "AS B"));
    bah.addUnit(FwUnit("Atemschutz C", "AS C"));

    bah.addUnit(FwUnit("Pikettzug", "Pikettzug"));

    bah.addUnit(FwUnit("Team Absturz", "Team-Abst."));

    bah.addUnit(FwUnit("Offiziere", "Kader"));
    bah.addUnit(FwUnit("Unteroffiziere", "Kader"));
}

