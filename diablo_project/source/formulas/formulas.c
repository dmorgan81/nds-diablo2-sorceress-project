int FormulaDam(lvl,dam,dam1,dam2,dam3,dam4,dam5)
{
    if (lvl==1) return dam;
    if (lvl>=2 && lvl<=8) return (dam+(lvl-1)*dam1);
    if (lvl>=9 && lvl<=16) return (dam+7*dam1+(lvl-8)*dam2);
    if (lvl>=17 && lvl<=22) return (dam+7*dam1+8*dam2+(lvl-16)*dam3);
    if (lvl>=23 && lvl<=28) return (dam+7*dam1+8*dam2+6*dam3+(lvl-22)*dam4);
    if (lvl>=29) return (dam+7*dam1+8*dam2+6*dam3+6*dam4+(lvl-28)*dam5);
}
int FormulaManaCost(lvl,manashift,mana,lvlmana)
{
    return (FormulaFloor(((Math.pow(2,manashift)/256)*((lvlmana*(lvl-1))+mana)),100));
}
int FormulaFloor(value,multiplikator)
{
    if (!multiplikator) multiplikator = 1;
    if (value<0) value = 0;
    else value = Math.floor(value*multiplikator)/multiplikator;
    return value;
}
int FormulaAvg(value)
{
    return FormulaFloor(value,2);
}
int FormulaCeil(value)
{
    return Math.ceil(value);
}
int FormulaLn(lvl,a,b)
{
    if (lvl>0) return a+((lvl-1)*b);
    else return 0;
}
int FormulaDm(lvl,a,b)
{
    return ((b-a)*Math.floor((110*lvl)/(lvl+6))/100) + a;
}
int FormulaLenght(lvl,len,len1,len2,len3)
{
    return (len+(lvl-1)*len1)/25;
}
int FormulaLenght2(len)
{
    return len/25;
}
int min(a,b)
{
    return Math.min(a,b);
}
int max(a,b)
{
    return Math.max(a,b);
}
int NoNiHe(dur,normal,nightmare,hell)
{
    difficuly = document.skills.diff.selectedIndex;
    if (difficuly==0) return dur*normal;
    if (difficuly==1) return dur*nightmare;
    if (difficuly==2) return dur*hell;
}
int NoNiHeCold(dur)
{
    return NoNiHe(dur,1,0.5,0.25);
}
int skill_off(span)
{
    document.getElementById(span).style.display = 'none';
    document.getElementById("auf_" + span).style.display = 'inline';
    document.getElementById("zu_" + span).style.display = 'none';
    return false;
}
int skill_on(span)
{
    document.getElementById(span).style.display = 'inline';
    document.getElementById("auf_" + span).style.display = 'none';
    document.getElementById("zu_" + span).style.display = 'inline';
    return false;
}
int skill_on_off(span)
{
    displayType = (document.getElementById(span).style.display == 'none') ? 'inline' : 'none';
    displayType2 = (document.getElementById(span).style.display == 'inline') ? 'inline' : 'none';
    document.getElementById(span).style.display = displayType;
    document.skills["open_" + span].value = 0;
    document.getElementById("auf_" + span).style.display = displayType2;
    document.getElementById("zu_" + span).style.display = displayType;
    return false;
}
int MonLvlAr(petlevel)
{
    difficulty = document.skills.diff.selectedIndex;
    if (petlevel>=110) return 6532;
    if (difficulty==0 && petlevel>5) return 45+11*(petlevel-6);
    if (difficulty==1 && petlevel>0) return 108+18*(petlevel-1);
    if (difficulty==2 && petlevel>0) return 216+38*(petlevel-1);
    unfug = new Array(1,8,12,18,26,35); //keine Formel für Level 1-5 in norm
    if (difficulty==0 && petlevel<6) return unfug[petlevel];
    return 1;
}
int MonLvlDef(petlevel)
{
    difficulty = document.skills.diff.selectedIndex;
    if (petlevel>=110) return 2100;
    if (difficulty==0 && petlevel>0) return 6*petlevel;
    if (difficulty==1 && petlevel>0) return 108+12*(petlevel-1);
    if (difficulty==2 && petlevel>0) return FormulaFloor(173+17.5*(petlevel-1));
    return 1;
}
