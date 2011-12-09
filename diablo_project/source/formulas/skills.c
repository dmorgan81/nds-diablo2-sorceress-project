function calc_36(lvl) { //Fire Bolt
	inv_47 = parseInt(document.skills.inv_47.selectedIndex);
	inv_56 = parseInt(document.skills.inv_56.selectedIndex);
	skill_61 = parseInt(document.skills.skill_61.value);
	DamModifier = 0.5;
	SynEMultiplicator = inv_47*16 + inv_56*16;
	EMinDam = FormulaDam(lvl,6,3,4,8,18,54);
	EMaxDam = FormulaDam(lvl,12,3,6,10,20,56);
	EMinDam = EMinDam*(1+SynEMultiplicator/100);
	EMaxDam = EMaxDam*(1+SynEMultiplicator/100);
	EMinDam = EMinDam*DamModifier;
	EMaxDam = EMaxDam*DamModifier;
	MasteryMultiplicator = parseInt(FormulaLn(skill_61,(30),(7)));
	if (skill_61==0) MasteryMultiplicator = 0;
	EMinDam = EMinDam*(1+MasteryMultiplicator/100);
	EMaxDam = EMaxDam*(1+MasteryMultiplicator/100);
	stats = new Array();
	i = 0;
	stats[i++] = 'Mana cost: ' + FormulaManaCost(lvl,7,5,0);
	stats[i++] = 'Fire damage: ' + FormulaFloor(EMinDam) + ' - ' + FormulaFloor(EMaxDam) + ' (ø' + FormulaAvg((EMinDam+EMaxDam)/2) + ')';
	stats[i++] = '[Synergy] Fire Ball: +' + (inv_47*16) + '% Fire damage (16% / Lvl)';
	stats[i++] = '[Synergy] Meteor: +' + (inv_56*16) + '% Fire damage (16% / Lvl)';
	return stats.join('\n');
}
//--------------------------------------------------------------
int calc_37(lvl) { //Warmth
	stats = new Array();
	i = 0;
	stats[i++] = 'Mana recovery: +' + FormulaLn(lvl,(30),(12)) + '%';
	return stats.join('\n');
}
//--------------------------------------------------------------
int calc_38(lvl) { //Charged Bolt
	inv_49 = parseInt(document.skills.inv_49.selectedIndex);
	skill_63 = parseInt(document.skills.skill_63.value);
	DamModifier = 0.5;
	SynEMultiplicator = inv_49*6;
	EMinDam = FormulaDam(lvl,4,1,1,2,3,4);
	EMaxDam = FormulaDam(lvl,8,1,1,2,3,4);
	EMinDam = EMinDam*(1+SynEMultiplicator/100);
	EMaxDam = EMaxDam*(1+SynEMultiplicator/100);
	EMinDam = EMinDam*DamModifier;
	EMaxDam = EMaxDam*DamModifier;
	MasteryMultiplicator = parseInt(FormulaLn(skill_63,(50),(12)));
	EMinDam = EMinDam*(1+MasteryMultiplicator/100);
	EMaxDam = EMaxDam*(1+MasteryMultiplicator/100);
	stats = new Array();
	i = 0;
	stats[i++] = 'Mana cost: ' + FormulaManaCost(lvl,5,24,4);
	stats[i++] = 'Lightning damage: ' + FormulaFloor(EMinDam) + ' - ' + FormulaFloor(EMaxDam) + ' (ø' + FormulaAvg((EMinDam+EMaxDam)/2) + ')';
	stats[i++] = 'Number of bolts: ' + min(24,FormulaLn(lvl,(3),(1)));
	stats[i++] = '[Synergy] Lightning: +' + (inv_49*6) + '% Lightning damage (6% / Lvl)';
	return stats.join('\n');
}
//--------------------------------------------------------------
int calc_39(lvl) { //Ice Bolt
	inv_44 = parseInt(document.skills.inv_44.selectedIndex);
	inv_45 = parseInt(document.skills.inv_45.selectedIndex);
	inv_55 = parseInt(document.skills.inv_55.selectedIndex);
	inv_59 = parseInt(document.skills.inv_59.selectedIndex);
	inv_64 = parseInt(document.skills.inv_64.selectedIndex);
	ELen = FormulaLenght(lvl,150,35,35,35);
	DamModifier = 0.5;
	SynEMultiplicator = inv_44*15 + inv_45*15 + inv_55*15 + inv_59*15 + inv_64*15;
	EMinDam = FormulaDam(lvl,6,2,4,6,8,10);
	EMaxDam = FormulaDam(lvl,10,3,5,7,9,11);
	EMinDam = EMinDam*(1+SynEMultiplicator/100);
	EMaxDam = EMaxDam*(1+SynEMultiplicator/100);
	EMinDam = EMinDam*DamModifier;
	EMaxDam = EMaxDam*DamModifier;
	stats = new Array();
	i = 0;
	stats[i++] = 'Mana cost: ' + FormulaManaCost(lvl,8,3,0);
	stats[i++] = 'Cold Duration: ' + FormulaFloor(NoNiHeCold(ELen),10) + ' Seconds';
	stats[i++] = 'Cold Damage: ' + FormulaFloor(EMinDam) + ' - ' + FormulaFloor(EMaxDam) + ' (ø' + FormulaAvg((EMinDam+EMaxDam)/2) + ')';
	stats[i++] = '[Synergy] Frost Nova: +' + (inv_44*15) + '% Cold Damage (15% / Lvl)';
	stats[i++] = '[Synergy] Ice Blast: +' + (inv_45*15) + '% Cold Damage (15% / Lvl)';
	stats[i++] = '[Synergy] Glacial Spike: +' + (inv_55*15) + '% Cold Damage (15% / Lvl)';
	stats[i++] = '[Synergy] Blizzard: +' + (inv_59*15) + '% Cold Damage (15% / Lvl)';
	stats[i++] = '[Synergy] Frozen Orb: +' + (inv_64*15) + '% Cold Damage (15% / Lvl)';
	return stats.join('\n');
}
//--------------------------------------------------------------
int calc_40(lvl) { //Frozen Armor
	inv_50 = parseInt(document.skills.inv_50.selectedIndex);
	inv_60 = parseInt(document.skills.inv_60.selectedIndex);
	inv_50 = parseInt(document.skills.inv_50.selectedIndex);
	inv_60 = parseInt(document.skills.inv_60.selectedIndex);
	Len = (FormulaLn(lvl,(3000),(300))+(inv_50+inv_60)*(250))/25;
	ELen = FormulaFloor((FormulaLn(lvl,(30),(3))*(100+((inv_50+inv_60)*(5)))/100)/25,10);
	stats = new Array();
	i = 0;
	stats[i++] = 'Mana cost: ' + FormulaManaCost(lvl,8,7,0);
	stats[i++] = 'Duration: ' + FormulaFloor(Len,10) + ' Seconds';
	stats[i++] = 'Defense: +' + FormulaLn(lvl,(30),(5)) + '%';
	stats[i++] = 'Cold Duration: ' + NoNiHeCold(ELen) + ' Seconds';
	//[38|39]] damagedinmelee: 2;
	stats[i++] = '[Synergy] Shiver Armor: +' + (inv_50*10) + ' Seconds (10 / Lvl)';
	stats[i++] = '[Synergy] Chilling Armor: +' + (inv_60*10) + ' Seconds (10 / Lvl)';
	stats[i++] = '[Synergy] Shiver Armor: +' + (inv_50*5) + '% Cold Duration (5% / Lvl)';
	stats[i++] = '[Synergy] Chilling Armor: +' + (inv_60*5) + '% Cold Duration (5% / Lvl)';
	return stats.join('\n');
}
//--------------------------------------------------------------
int calc_41(lvl) { //Inferno
	inv_37 = parseInt(document.skills.inv_37.selectedIndex);
	skill_61 = parseInt(document.skills.skill_61.value);
	DamModifier = 4;
	SynEMultiplicator = inv_37*13;
	EMinDam = FormulaDam(lvl,32,24,26,28,32,36);
	EMaxDam = FormulaDam(lvl,64,24,27,29,33,37);
	EMinDam = EMinDam*DamModifier;
	EMaxDam = EMaxDam*DamModifier;
	EMinDam = EMinDam*(1+SynEMultiplicator/100);
	EMaxDam = EMaxDam*(1+SynEMultiplicator/100);
	MasteryMultiplicator = parseInt(FormulaLn(skill_61,(30),(7)));
	EMinDam = EMinDam*(1+MasteryMultiplicator/100);
	EMaxDam = EMaxDam*(1+MasteryMultiplicator/100);
	//BUG:
	EMinDam = EMinDam*25/2;
	EMaxDam = EMaxDam*25/2;
	EMinDam = EMinDam/256;
	EMaxDam = EMaxDam/256;
	stats = new Array();
	i = 0;
	stats[i++] = 'Mana cost: ' + FormulaFloor(((1/128)*((1*(lvl-1))+36))*25);
	stats[i++] = 'Minimum mana to cast: ' + 6;
	stats[i++] = 'Range: ' + FormulaFloor((FormulaLn(lvl,(20),(3))/4)*(2/3),10) + ' Yards';
	stats[i++] = 'Fire damage: ' + FormulaFloor(EMinDam) + ' - ' + FormulaFloor(EMaxDam) + ' (ø' + FormulaAvg((EMinDam+EMaxDam)/2) + ')';
	//[189|188]] frames if monster: 20;
	stats[i++] = '[Synergy] Warmth: +' + (inv_37*13) + '% Fire damage (13% / Lvl)';
	return stats.join('\n');
}
//--------------------------------------------------------------
int calc_42(lvl) { //Static Field
	stats = new Array();
	i = 0;
	stats[i++] = 'Mana cost: ' + FormulaManaCost(lvl,8,9,0);
	stats[i++] = 'Range: ' + FormulaFloor((FormulaLn(lvl,(5),(1)))*(2/3),10) + ' Yards';
	stats[i++] = 'Enemy hit points: -25%';
	//[189|188]] min damage: (0);
	return stats.join('\n');
}
//--------------------------------------------------------------
int calc_43(lvl) { //Telekinesis
	skill_63 = parseInt(document.skills.skill_63.value);
	EMinDam = FormulaDam(lvl,1,1,1,1,1,1);
	EMaxDam = FormulaDam(lvl,2,1,1,1,1,1);
	MasteryMultiplicator = parseInt(FormulaLn(skill_63,(50),(12)));
	EMinDam = EMinDam*(1+MasteryMultiplicator/100);
	EMaxDam = EMaxDam*(1+MasteryMultiplicator/100);
	stats = new Array();
	i = 0;
	stats[i++] = 'Mana cost: ' + FormulaManaCost(lvl,8,7,0);
	stats[i++] = 'Range: ' + FormulaFloor(((25))*(2/3),10) + ' Yards';
	stats[i++] = 'Lightning damage: ' + FormulaFloor(EMinDam) + ' - ' + FormulaFloor(EMaxDam) + ' (ø' + FormulaAvg((EMinDam+EMaxDam)/2) + ')';
	stats[i++] = 'Chance to knockback/stun: 35%';
	return stats.join('\n');
}
//--------------------------------------------------------------
int calc_44(lvl) { //Frost Nova
	inv_59 = parseInt(document.skills.inv_59.selectedIndex);
	inv_64 = parseInt(document.skills.inv_64.selectedIndex);
	ELen = FormulaLenght(lvl,200,25,25,25);
	DamModifier = 0.5;
	SynEMultiplicator = inv_59*10 + inv_64*10;
	EMinDam = FormulaDam(lvl,4,4,6,8,10,12);
	EMaxDam = FormulaDam(lvl,8,5,7,9,11,13);
	EMinDam = EMinDam*(1+SynEMultiplicator/100);
	EMaxDam = EMaxDam*(1+SynEMultiplicator/100);
	EMinDam = EMinDam*DamModifier;
	EMaxDam = EMaxDam*DamModifier;
	stats = new Array();
	i = 0;
	stats[i++] = 'Mana cost: ' + FormulaManaCost(lvl,8,9,1);
	stats[i++] = 'Cold Duration: ' + NoNiHeCold(ELen) + ' Seconds';
	stats[i++] = 'Cold Damage: ' + FormulaFloor(EMinDam) + ' - ' + FormulaFloor(EMaxDam) + ' (ø' + FormulaAvg((EMinDam+EMaxDam)/2) + ')';
	//stats[i++] = 'Cold Radius: ' + FormulaFloor(FormulaLn(lvl,9,3)*(2/3),10) + ' Yards';
	stats[i++] = 'Cold Radius: 7.4 Yards';
	stats[i++] = '[Synergy] Blizzard: +' + (inv_59*10) + '% Cold Damage (10% / Lvl)';
	stats[i++] = '[Synergy] Frozen Orb: +' + (inv_64*10) + '% Cold Damage (10% / Lvl)';
	return stats.join('\n');
}
//--------------------------------------------------------------
int calc_45(lvl) { //Ice Blast
	inv_39 = parseInt(document.skills.inv_39.selectedIndex);
	inv_59 = parseInt(document.skills.inv_59.selectedIndex);
	inv_64 = parseInt(document.skills.inv_64.selectedIndex);
	inv_55 = parseInt(document.skills.inv_55.selectedIndex);
	ELen = FormulaLenght(lvl,75,5,5,5);
	DamModifier = 0.5;
	SynEMultiplicator = inv_39*8 + inv_59*8 + inv_64*8;
	EMinDam = FormulaDam(lvl,16,14,28,42,56,70);
	EMaxDam = FormulaDam(lvl,24,15,29,43,57,71);
	EMinDam = EMinDam*(1+SynEMultiplicator/100);
	EMaxDam = EMaxDam*(1+SynEMultiplicator/100);
	EMinDam = EMinDam*DamModifier;
	EMaxDam = EMaxDam*DamModifier;
	SynLenMultiplicator = inv_55*10;
	ELen = ELen*(1+SynLenMultiplicator/100);
	stats = new Array();
	i = 0;
	stats[i++] = 'Mana cost: ' + FormulaManaCost(lvl,7,12,1);
	stats[i++] = 'Cold Duration: ' + FormulaFloor(NoNiHeCold(ELen),10) + ' Seconds';
	stats[i++] = 'Cold Damage: ' + FormulaFloor(EMinDam) + ' - ' + FormulaFloor(EMaxDam) + ' (ø' + FormulaAvg((EMinDam+EMaxDam)/2) + ')';
	stats[i++] = '[Synergy] Ice Bolt: +' + (inv_39*8) + '% Cold Damage (8% / Lvl)';
	stats[i++] = '[Synergy] Blizzard: +' + (inv_59*8) + '% Cold Damage (8% / Lvl)';
	stats[i++] = '[Synergy] Frozen Orb: +' + (inv_64*8) + '% Cold Damage (8% / Lvl)';
	stats[i++] = '[Synergy] Glacial Spike: +' + (inv_55*10) + '% Cold Duration (10% / Lvl)';
	return stats.join('\n');
}
//--------------------------------------------------------------
int calc_46(lvl) { //Blaze
	skill_61 = parseInt(document.skills.skill_61.value);
	inv_37 = parseInt(document.skills.inv_37.value);
	inv_51 = parseInt(document.skills.inv_51.value);
	Len = (FormulaDm(lvl,(50),(500)))/25;
	DamModifier = 4.8*25/256*10;
	SynEMultiplicator = inv_37*4 + inv_51*1;
	EMinDam = FormulaDam(lvl,4,2,3,4,6,9);
	EMaxDam = FormulaDam(lvl,8,2,3,4,6,9);
	EMinDam = EMinDam*(1+SynEMultiplicator/100);
	EMaxDam = EMaxDam*(1+SynEMultiplicator/100);
	EMinDam = EMinDam*DamModifier;
	EMaxDam = EMaxDam*DamModifier;
	MasteryMultiplicator = parseInt(FormulaLn(skill_61,(30),(7)));
	EMinDam = EMinDam*(1+MasteryMultiplicator/100);
	EMaxDam = EMaxDam*(1+MasteryMultiplicator/100);
	Len = FormulaFloor(Len,10);
	stats = new Array();
	i = 0;
	stats[i++] = 'Mana cost: ' + FormulaManaCost(lvl,7,22,1);
	stats[i++] = 'Duration: ' + FormulaFloor(Len,10) + ' Seconds';
	stats[i++] = 'Fire damage: ' + FormulaFloor(EMinDam) + ' - ' + FormulaFloor(EMaxDam) + ' (ø' + FormulaAvg((EMinDam+EMaxDam)/2) + ')';
	stats[i++] = '[Synergy] Warmth: +' + (inv_37*4) + '% Fire damage (4% / Lvl)';
	stats[i++] = '[Synergy] Fire Wall: +' + (inv_51*1) + '% Fire damage (1% / Lvl)';
	return stats.join('\n');
}
//--------------------------------------------------------------
int calc_47(lvl) { //Fire Ball
	inv_36 = parseInt(document.skills.inv_36.selectedIndex);
	inv_56 = parseInt(document.skills.inv_56.selectedIndex);
	skill_61 = parseInt(document.skills.skill_61.value);
	DamModifier = 0.5;
	SynEMultiplicator = inv_36*14 + inv_56*14;
	EMinDam = FormulaDam(lvl,12,13,23,28,33,38);
	EMaxDam = FormulaDam(lvl,28,15,25,30,35,40);
	EMinDam = EMinDam*(1+SynEMultiplicator/100);
	EMaxDam = EMaxDam*(1+SynEMultiplicator/100);
	EMinDam = EMinDam*DamModifier;
	EMaxDam = EMaxDam*DamModifier;
	MasteryMultiplicator = parseInt(FormulaLn(skill_61,(30),(7)));
	EMinDam = EMinDam*(1+MasteryMultiplicator/100);
	EMaxDam = EMaxDam*(1+MasteryMultiplicator/100);
	stats = new Array();
	i = 0;
	stats[i++] = 'Mana cost: ' + FormulaManaCost(lvl,7,10,1);
	stats[i++] = 'Fire damage: ' + FormulaFloor(EMinDam) + ' - ' + FormulaFloor(EMaxDam) + ' (ø' + FormulaAvg((EMinDam+EMaxDam)/2) + ')';
	stats[i++] = '[Synergy] Fire Bolt: +' + (inv_36*14) + '% Fire damage (14% / Lvl)';
	stats[i++] = '[Synergy] Meteor: +' + (inv_56*14) + '% Fire damage (14% / Lvl)';
	return stats.join('\n');
}
//--------------------------------------------------------------
int calc_48(lvl) { //Nova
	skill_63 = parseInt(document.skills.skill_63.value);
	EMinDam = FormulaDam(lvl,1,6,7,8,9,10);
	EMaxDam = FormulaDam(lvl,20,8,9,10,11,12);
	MasteryMultiplicator = parseInt(FormulaLn(skill_63,(50),(12)));
	EMinDam = EMinDam*(1+MasteryMultiplicator/100);
	EMaxDam = EMaxDam*(1+MasteryMultiplicator/100);
	stats = new Array();
	i = 0;
	stats[i++] = 'Mana cost: ' + FormulaManaCost(lvl,8,15,1);
	stats[i++] = 'Lightning damage: ' + FormulaFloor(EMinDam) + ' - ' + FormulaFloor(EMaxDam) + ' (ø' + FormulaAvg((EMinDam+EMaxDam)/2) + ')';
	stats[i++] = 'Radius: 7.4 Yards';
	//[195|194] number of missiles: 12;
	//[197|196] additional missiles per level: 4;
	return stats.join('\n');
}
//--------------------------------------------------------------
int calc_49(lvl) { //Lightning
	inv_38 = parseInt(document.skills.inv_38.selectedIndex);
	inv_53 = parseInt(document.skills.inv_53.selectedIndex);
	inv_48 = parseInt(document.skills.inv_48.selectedIndex);
	skill_63 = parseInt(document.skills.skill_63.value);
	SynEMultiplicator = inv_38*8 + inv_53*8 + inv_48*8;
	EMinDam = 1;
	EMaxDam = FormulaDam(lvl,40,8,12,20,28,36);
	//EMinDam = EMinDam*(1+SynEMultiplicator/100);
	EMaxDam = EMaxDam*(1+SynEMultiplicator/100);
	MasteryMultiplicator = parseInt(FormulaLn(skill_63,(50),(12)));
	EMinDam = EMinDam*(1+MasteryMultiplicator/100);
	EMaxDam = EMaxDam*(1+MasteryMultiplicator/100);
	stats = new Array();
	i = 0;
	stats[i++] = 'Mana cost: ' + FormulaManaCost(lvl,7,16,1);
	stats[i++] = 'Lightning damage: ' + FormulaFloor(EMinDam) + ' - ' + FormulaFloor(EMaxDam) + ' (ø' + FormulaAvg((EMinDam+EMaxDam)/2) + ')';
	//[195|194] minimum damage: 10;
	//[197|196] max damage: 20;
	//[199|198] increase in dam/level (min & max): 4;
	stats[i++] = '[Synergy] Charged Bolt: +' + (inv_38*8) + '% Lightning damage (8% / Lvl)';
	stats[i++] = '[Synergy] Chain Lightning: +' + (inv_53*8) + '% Lightning damage (8% / Lvl)';
	stats[i++] = '[Synergy] Nova: +' + (inv_48*8) + '% Lightning damage (8% / Lvl)';
	return stats.join('\n');
}
//--------------------------------------------------------------
int calc_50(lvl) { //Shiver Armor
	inv_40 = parseInt(document.skills.inv_40.selectedIndex);
	inv_60 = parseInt(document.skills.inv_60.selectedIndex);
	inv_40 = parseInt(document.skills.inv_40.selectedIndex);
	inv_60 = parseInt(document.skills.inv_60.selectedIndex);
	Len = (FormulaLn(lvl,(3000),(300))+(inv_40+inv_60)*(250))/25;
	ELen = FormulaLenght2(100);
	DamModifier = 0.5;
	SynEMultiplicator = inv_40*9 + inv_60*9;
	EMinDam = FormulaDam(lvl,12,4,6,8,10,12);
	EMaxDam = FormulaDam(lvl,16,5,7,9,11,13);
	EMinDam = EMinDam*(1+SynEMultiplicator/100);
	EMaxDam = EMaxDam*(1+SynEMultiplicator/100);
	EMinDam = EMinDam*DamModifier;
	EMaxDam = EMaxDam*DamModifier;
	stats = new Array();
	i = 0;
	stats[i++] = 'Mana cost: ' + FormulaManaCost(lvl,8,11,0);
	stats[i++] = 'Duration: ' + FormulaFloor(Len,10) + ' Seconds';
	stats[i++] = 'Cold Duration: ' + NoNiHeCold(ELen) + ' Seconds';
	stats[i++] = 'Cold Damage: ' + FormulaFloor(EMinDam) + ' - ' + FormulaFloor(EMaxDam) + ' (ø' + FormulaAvg((EMinDam+EMaxDam)/2) + ')';
	stats[i++] = 'Defense: ' + FormulaLn(lvl,(45),(6)) + '%';
	//[38|39]] attackedinmelee: 3;
	//[102|101] sparkle delay: 10;
	//[104|103] sparkle radius: 5;
	//[106|105] sparkle height: 3;
	stats[i++] = '[Synergy] Frozen Armor: +' + (inv_40*10) + ' Seconds (10 / Lvl)';
	stats[i++] = '[Synergy] Chilling Armor: +' + (inv_60*10) + ' Seconds (10 / Lvl)';
	stats[i++] = '[Synergy] Frozen Armor: +' + (inv_40*9) + '% Cold Damage (9% / Lvl)';
	stats[i++] = '[Synergy] Chilling Armor: +' + (inv_60*9) + '% Cold Damage (9% / Lvl)';
	return stats.join('\n');
}
//--------------------------------------------------------------
int calc_51(lvl) { //Fire Wall
	skill_61 = parseInt(document.skills.skill_61.value);
	inv_37 = parseInt(document.skills.inv_37.value);
	inv_41 = parseInt(document.skills.inv_41.value);
	DamModifier = 4.8*25/256*10;
	SynEMultiplicator = inv_37*4 + inv_41*1; // bashiok schreibt 1% für blaze, ingame 0%
	EMinDam = FormulaDam(lvl,15,9,14,21,21,21);
	EMaxDam = FormulaDam(lvl,20,9,14,21,21,21);
	EMinDam = EMinDam*(1+SynEMultiplicator/100);
	EMaxDam = EMaxDam*(1+SynEMultiplicator/100);
	EMinDam = EMinDam*DamModifier;
	EMaxDam = EMaxDam*DamModifier;
	MasteryMultiplicator = parseInt(FormulaLn(skill_61,(30),(7)));
	EMinDam = EMinDam*(1+MasteryMultiplicator/100);
	EMaxDam = EMaxDam*(1+MasteryMultiplicator/100);
	stats = new Array();
	i = 0;
	stats[i++] = 'Mana cost: ' + FormulaManaCost(lvl,8,22,1);
	stats[i++] = 'Cast Delay: 1.4 Seconds';
	stats[i++] = 'Fire damage: ' + FormulaFloor(EMinDam) + ' - ' + FormulaFloor(EMaxDam) + ' (ø' + FormulaAvg((EMinDam+EMaxDam)/2) + ')';
	stats[i++] = 'Duration: 3.6 Seconds';
	stats[i++] = 'Length: ' + FormulaFloor(FormulaLn(lvl,4.85,1.4),10) + ' Yards';
	stats[i++] = '[Synergy] Warmth: +' + (inv_37*4) + '% Fire damage (4% / Lvl)';
	stats[i++] = '[Synergy] Inferno: +' + (inv_41*1) + '% Fire damage (1% / Lvl)';
	return stats.join('\n');
}
//--------------------------------------------------------------
int calc_52(lvl) { //Enchant
	inv_37 = parseInt(document.skills.inv_37.selectedIndex);
	skill_61 = parseInt(document.skills.skill_61.value);
	Len = (FormulaLn(lvl,(3600),(600)))/25;
	DamModifier = 0.5;
	SynEMultiplicator = inv_37*9;
	EMinDam = FormulaDam(lvl,16,3,7,11,15,19);
	EMaxDam = FormulaDam(lvl,20,5,9,13,17,21);
	EMinDam = EMinDam*(1+SynEMultiplicator/100);
	EMaxDam = EMaxDam*(1+SynEMultiplicator/100);
	EMinDam = EMinDam*DamModifier;
	EMaxDam = EMaxDam*DamModifier;
	MasteryMultiplicator = parseInt(FormulaLn(skill_61,(30),(7)));
	EMinDam = EMinDam*(1+MasteryMultiplicator/100);
	EMaxDam = EMaxDam*(1+MasteryMultiplicator/100);
	EMinDamSelf = EMinDam*(1+MasteryMultiplicator/100);
	EMaxDamSelf = EMaxDam*(1+MasteryMultiplicator/100);
	stats = new Array();
	i = 0;
	stats[i++] = 'Mana cost: ' + FormulaManaCost(lvl,8,25,1);
	stats[i++] = 'Duration: ' + FormulaFloor(Len,10) + ' Seconds';
	stats[i++] = 'Attack Rating: +' + (20 + (lvl-1)*9) + '%';
	stats[i++] = 'Fire damage: ' + FormulaFloor(EMinDam) + ' - ' + FormulaFloor(EMaxDam) + ' (ø' + FormulaAvg((EMinDam+EMaxDam)/2) + ')';
	//stats[i++] = 'Fire damage: ' + FormulaFloor(EMinDamSelf) + ' - ' + FormulaFloor(EMaxDamSelf) + ' (ø' + FormulaAvg((EMinDamSelf+EMaxDamSelf)/2) + ')';
	//[199|198] missile pct: 33;
	stats[i++] = '[Synergy] Warmth: +' + (inv_37*9) + '% Fire damage (9% / Lvl)';
	return stats.join('\n');
}
//--------------------------------------------------------------
int calc_53(lvl) { //Chain Lightning
	inv_38 = parseInt(document.skills.inv_38.selectedIndex);
	inv_49 = parseInt(document.skills.inv_49.selectedIndex);
	inv_48 = parseInt(document.skills.inv_48.selectedIndex);
	skill_63 = parseInt(document.skills.skill_63.value);
	SynEMultiplicator = inv_38*4 + inv_49*4 + inv_48*4;
	EMinDam = 1;
	EMaxDam = FormulaDam(lvl,40,11,13,15,15,15);
	//EMinDam = EMinDam*(1+SynEMultiplicator/100);
	EMaxDam = EMaxDam*(1+SynEMultiplicator/100);
	MasteryMultiplicator = parseInt(FormulaLn(skill_63,(50),(12)));
	EMinDam = EMinDam*(1+MasteryMultiplicator/100);
	EMaxDam = EMaxDam*(1+MasteryMultiplicator/100);
	stats = new Array();
	i = 0;
	stats[i++] = 'Mana cost: ' + FormulaManaCost(lvl,8,9,1);
	stats[i++] = 'Range: ' + FormulaFloor(((20))*(2/3),10) + ' Yards';
	stats[i++] = 'Lightning damage: ' + FormulaFloor(EMinDam) + ' - ' + FormulaFloor(EMaxDam) + ' (ø' + FormulaAvg((EMinDam+EMaxDam)/2) + ')';
	stats[i++] = 'Number of hits: ' + FormulaFloor(FormulaLn(lvl,(26),(1)) / 5);
	//[203|202] 5ths: 5;
	stats[i++] = '[Synergy] Charged Bolt: +' + (inv_38*4) + '% Lightning damage (4% / Lvl)';
	stats[i++] = '[Synergy] Lightning: +' + (inv_49*4) + '% Lightning damage (4% / Lvl)';
	stats[i++] = '[Synergy] Nova: +' + (inv_48*4) + '% Lightning damage (4% / Lvl)';
	return stats.join('\n');
}
//--------------------------------------------------------------
int calc_54(lvl) { //Teleport
	stats = new Array();
	i = 0;
	stats[i++] = 'Mana cost: ' + Math.max(1, FormulaManaCost(lvl,8,24,-1));
	return stats.join('\n');
}
//--------------------------------------------------------------
int calc_55(lvl) { //Glacial Spike
	inv_39 = parseInt(document.skills.inv_39.selectedIndex);
	inv_45 = parseInt(document.skills.inv_45.selectedIndex);
	inv_64 = parseInt(document.skills.inv_64.selectedIndex);
	inv_59 = parseInt(document.skills.inv_59.selectedIndex);
	Len = (FormulaLn(lvl,(50),(3)) * (100 + inv_59 * (3)) / 100)/25;
	DamModifier = 0.5;
	SynEMultiplicator = inv_39*5 + inv_45*5 + inv_64*5;
	EMinDam = FormulaDam(lvl,32,14,26,28,30,32);
	EMaxDam = FormulaDam(lvl,48,15,27,29,31,33);
	EMinDam = EMinDam*(1+SynEMultiplicator/100);
	EMaxDam = EMaxDam*(1+SynEMultiplicator/100);
	EMinDam = EMinDam*DamModifier;
	EMaxDam = EMaxDam*DamModifier;
	stats = new Array();
	i = 0;
	stats[i++] = 'Mana cost: ' + FormulaManaCost(lvl,7,20,1);
	stats[i++] = 'Duration: ' + NoNiHeCold(FormulaFloor(Len,10)) + ' Seconds';
	stats[i++] = 'Range: ' + FormulaFloor((FormulaLn(lvl,(4),(0)))*(2/3),10) + ' Yards';
	stats[i++] = 'Cold Damage: ' + FormulaFloor(EMinDam) + ' - ' + FormulaFloor(EMaxDam) + ' (ø' + FormulaAvg((EMinDam+EMaxDam)/2) + ')';
	stats[i++] = '[Synergy] Ice Bolt: +' + (inv_39*5) + '% Cold Damage (5% / Lvl)';
	stats[i++] = '[Synergy] Ice Blast: +' + (inv_45*5) + '% Cold Damage (5% / Lvl)';
	stats[i++] = '[Synergy] Frozen Orb: +' + (inv_64*5) + '% Cold Damage (5% / Lvl)';
	stats[i++] = '[Synergy] Blizzard: +' + (inv_59*3) + '% Cold Duration (3% / Lvl)';
	return stats.join('\n');
}
//--------------------------------------------------------------
int calc_56(lvl) { //Meteor
	inv_36 = parseInt(document.skills.inv_36.selectedIndex);
	inv_47 = parseInt(document.skills.inv_47.selectedIndex);
	skill_61 = parseInt(document.skills.skill_61.value);
	inv_41 = parseInt(document.skills.inv_41.selectedIndex);
	SynEMultiplicator = inv_36*5 + inv_47*5;
	EMinDam = FormulaDam(lvl,80,23,39,79,81,83);
	EMaxDam = FormulaDam(lvl,100,25,41,81,83,85);
	EMinDam = EMinDam*(1+SynEMultiplicator/100);
	EMaxDam = EMaxDam*(1+SynEMultiplicator/100);
	MasteryMultiplicator = parseInt(FormulaLn(skill_61,(30),(7)));
	EMinDam = EMinDam*(1+MasteryMultiplicator/100);
	EMaxDam = EMaxDam*(1+MasteryMultiplicator/100);
	EFireMinDam = FormulaDam(lvl,15,4,5,6,6,6);
	EFireMaxDam = FormulaDam(lvl,25,4,5,6,6,6);
	SynEFireMultiplicator = inv_41*3;
	EFireMinDam = EFireMinDam*(1+SynEFireMultiplicator/100);
	EFireMaxDam = EFireMaxDam*(1+SynEFireMultiplicator/100);
	FireDamModifier = 2.34375; // hitshift-technikkram, bei Rückfragen an mfb wenden
	EFireMinDam = EFireMinDam*FireDamModifier;
	EFireMaxDam = EFireMaxDam*FireDamModifier;
	EFireMinDam = EFireMinDam*(1+MasteryMultiplicator/100);
	EFireMaxDam = EFireMaxDam*(1+MasteryMultiplicator/100);
	stats = new Array();
	i = 0;
	stats[i++] = 'Mana cost: ' + FormulaManaCost(lvl,7,34,1);
	stats[i++] = 'Cast Delay: 1.2 Seconds';
	stats[i++] = 'Range: ' + FormulaFloor((FormulaLn(lvl,(6),(0)))*(2/3),10) + ' Yards';
	stats[i++] = 'Fire damage: ' + FormulaFloor(EMinDam) + ' - ' + FormulaFloor(EMaxDam) + ' (ø' + FormulaAvg((EMinDam+EMaxDam)/2) + ')';
	stats[i++] = 'Fire damage per second: ' + FormulaFloor(EFireMinDam) + ' - ' + FormulaFloor(EFireMaxDam) + '(ø ' + FormulaFloor((EFireMinDam+EFireMaxDam)/2) + ')';
	stats[i++] = 'Fire lenght: ' + FormulaFloor(FormulaLn(lvl,30/25,15/25),10) + ' Seconds';
	stats[i++] = '[Synergy] Fire Bolt: +' + (inv_36*5) + '% Fire damage (5% / Lvl)';
	stats[i++] = '[Synergy] Fire Ball: +' + (inv_47*5) + '% Fire damage (5% / Lvl)';
	stats[i++] = '[Synergy] Inferno: +' + (inv_41*3) + '% Fire damage per second (3% / Lvl)';
	return stats.join('\n');
}
//--------------------------------------------------------------
int calc_57(lvl) { //Thunder Storm
	skill_63 = parseInt(document.skills.skill_63.value);
	Len = (FormulaLn(lvl,(800),(200)))/25;
	EMinDam = FormulaDam(lvl,1,10,10,11,11,11);
	EMaxDam = FormulaDam(lvl,100,10,10,11,11,11);
	MasteryMultiplicator = parseInt(FormulaLn(skill_63,(50),(12)));
	EMinDam = EMinDam*(1+MasteryMultiplicator/100);
	EMaxDam = EMaxDam*(1+MasteryMultiplicator/100);
	stats = new Array();
	i = 0;
	stats[i++] = 'Mana cost: ' + FormulaManaCost(lvl,8,19,0);
	stats[i++] = 'Deals damage every ' + FormulaFloor(((100-FormulaDm(lvl,(0),(100))) * (100)/100 + (25))/25,10) + ' Seconds';
	stats[i++] = 'Duration: ' + FormulaFloor(Len,10) + ' Seconds';
	stats[i++] = 'Lightning damage: ' + FormulaFloor(EMinDam) + ' - ' + FormulaFloor(EMaxDam) + ' (ø' + FormulaAvg((EMinDam+EMaxDam)/2) + ')';
	stats[i++] = 'Radius: ' + FormulaFloor(17*(2/3)) + ' Yards';
	return stats.join('\n');
}
//--------------------------------------------------------------
int calc_58(lvl) { //Energy Shield
	inv_43 = parseInt(document.skills.inv_43.selectedIndex);
	Len = (FormulaLn(lvl,(3600),(1500)))/25;
	Value = FormulaDam(lvl,20,5,2,1,1,1);
	stats = new Array();
	i = 0;
	stats[i++] = 'Mana cost: ' + FormulaManaCost(lvl,8,5,0);
	stats[i++] = 'Duration: ' + FormulaFloor(Len,10) + ' Seconds';
	stats[i++] = 'Absorbs Damage: ' + min(FormulaDam(lvl,20,5,2,1,1,1),95) + '%';
	stats[i++] = 'Absorb Multiplikator: ' + FormulaFloor((32-inv_43)/16,100);
	stats[i++] = '[Synergy] Telekinesis: -' + (inv_43*6.25) + '% Absorb multiplier (-6.25% / Lvl)';
	return stats.join('\n');
}
//--------------------------------------------------------------
int calc_59(lvl) { //Blizzard
	inv_39 = parseInt(document.skills.inv_39.selectedIndex);
	inv_45 = parseInt(document.skills.inv_45.selectedIndex);
	inv_55 = parseInt(document.skills.inv_55.selectedIndex);
	ELen = FormulaLenght2(100);
	SynEMultiplicator = inv_39*5 + inv_45*5 + inv_55*5;
	EMinDam = FormulaDam(lvl,45,15,30,45,55,65);
	EMaxDam = FormulaDam(lvl,75,16,31,46,56,66);
	EMinDam = EMinDam*(1+SynEMultiplicator/100);
	EMaxDam = EMaxDam*(1+SynEMultiplicator/100);
	stats = new Array();
	i = 0;
	stats[i++] = 'Mana cost: ' + FormulaManaCost(lvl,8,23,1);
	stats[i++] = 'Cast Delay: 1.8 Seconds';
	stats[i++] = 'Cold Duration: ' + NoNiHeCold(ELen) + ' Seconds';
	stats[i++] = 'Cold Damage: ' + FormulaFloor(EMinDam) + ' - ' + FormulaFloor(EMaxDam) + ' (ø' + FormulaAvg((EMinDam+EMaxDam)/2) + ')';
	stats[i++] = 'Radius: ' + FormulaFloor(7*(2/3)) + ' Yards';
	//[189|188]] frequency: (4);
	stats[i++] = '[Synergy] Ice Bolt: +' + (inv_39*5) + '% Cold Damage (5% / Lvl)';
	stats[i++] = '[Synergy] Ice Blast: +' + (inv_45*5) + '% Cold Damage (5% / Lvl)';
	stats[i++] = '[Synergy] Glacial Spike: +' + (inv_55*5) + '% Cold Damage (5% / Lvl)';
	return stats.join('\n');
}
//--------------------------------------------------------------
int calc_60(lvl) { //Chilling Armor
	inv_40 = parseInt(document.skills.inv_40.selectedIndex);
	inv_50 = parseInt(document.skills.inv_50.selectedIndex);
	inv_40 = parseInt(document.skills.inv_40.selectedIndex);
	inv_50 = parseInt(document.skills.inv_50.selectedIndex);
	Len = (FormulaLn(lvl,(3600),(150))+(inv_40+inv_50)*(250))/25;
	ELen = FormulaLenght2(100);
	DamModifier = 0.5;
	SynEMultiplicator = inv_40*7 + inv_50*7;
	EMinDam = FormulaDam(lvl,8,2,4,6,8,10);
	EMaxDam = FormulaDam(lvl,12,3,5,7,9,11);
	EMinDam = EMinDam*(1+SynEMultiplicator/100);
	EMaxDam = EMaxDam*(1+SynEMultiplicator/100);
	EMinDam = EMinDam*DamModifier;
	EMaxDam = EMaxDam*DamModifier;
	stats = new Array();
	i = 0;
	stats[i++] = 'Mana cost: ' + FormulaManaCost(lvl,8,17,0);
	stats[i++] = 'Duration: ' + FormulaFloor(Len,10) + ' Seconds';
	stats[i++] = 'Cold Duration: ' + NoNiHeCold(ELen) + ' Seconds';
	stats[i++] = 'Cold Damage: ' + FormulaFloor(EMinDam) + ' - ' + FormulaFloor(EMaxDam) + ' (ø' + FormulaAvg((EMinDam+EMaxDam)/2) + ')';
	stats[i++] = 'Defense: ' + FormulaLn(lvl,(45),(5)) + '%';
	//[38|39]] hitbymissile: 1;
	stats[i++] = '[Synergy] Frozen Armor: +' + (inv_40*10) + ' Seconds (10 / Lvl)';
	stats[i++] = '[Synergy] Shiver Armor: +' + (inv_50*10) + ' Seconds (10 / Lvl)';
	stats[i++] = '[Synergy] Frozen Armor: +' + (inv_40*7) + '% Cold Damage (7% / Lvl)';
	stats[i++] = '[Synergy] Shiver Armor: +' + (inv_50*7) + '% Cold Damage (7% / Lvl)';
	return stats.join('\n');
}
//--------------------------------------------------------------
int calc_61(lvl) { //Fire Mastery
	stats = new Array();
	i = 0;
	stats[i++] = 'Fire damage: +' + FormulaLn(lvl,(30),(7)) + '%';
	return stats.join('\n');
}
//--------------------------------------------------------------
int calc_62(lvl) { //Hydra
	inv_36 = parseInt(document.skills.inv_36.selectedIndex);
	inv_47 = parseInt(document.skills.inv_47.selectedIndex);
	skill_61 = parseInt(document.skills.skill_61.value);
	DamModifier = 0.5;
	SynEMultiplicator = inv_36*3 + inv_47*3;
	EMinDam = FormulaDam(lvl,24,9,13,17,21,25);
	EMaxDam = FormulaDam(lvl,34,11,15,19,23,27);
	EMinDam = EMinDam*(1+SynEMultiplicator/100);
	EMaxDam = EMaxDam*(1+SynEMultiplicator/100);
	EMinDam = EMinDam*DamModifier;
	EMaxDam = EMaxDam*DamModifier;
	MasteryMultiplicator = parseInt(FormulaLn(skill_61,(30),(7)));
	EMinDam = EMinDam*(1+MasteryMultiplicator/100);
	EMaxDam = EMaxDam*(1+MasteryMultiplicator/100);
	stats = new Array();
	i = 0;
	stats[i++] = 'Mana cost: ' + FormulaManaCost(lvl,7,40,1);
	stats[i++] = 'Cast Delay: 1.6 Seconds';
	stats[i++] = 'Fire damage: ' + FormulaFloor(EMinDam) + ' - ' + FormulaFloor(EMaxDam) + ' (ø' + FormulaAvg((EMinDam+EMaxDam)/2) + ')';
	stats[i++] = 'Duration: 10 Seconds';
	stats[i++] = '[Synergy] Fire Bolt: +' + (inv_36*3) + '% Fire damage (3% / Lvl)';
	stats[i++] = '[Synergy] Fire Ball: +' + (inv_47*3) + '% Fire damage (3% / Lvl)';
	return stats.join('\n');
}
//--------------------------------------------------------------
int calc_63(lvl) { //Lightning Mastery
	stats = new Array();
	i = 0;
	stats[i++] = 'Lightning damage: +' + FormulaLn(lvl,50,12) + '%';
	return stats.join('\n');
}
//--------------------------------------------------------------
int calc_64(lvl) { //Frozen Orb
	inv_39 = parseInt(document.skills.inv_39.selectedIndex);
	ELen = FormulaLenght(lvl,200,25,25,25);
	DamModifier = 0.5;
	SynEMultiplicator = inv_39*2;
	EMinDam = FormulaDam(lvl,80,20,24,28,29,30);
	EMaxDam = FormulaDam(lvl,90,21,25,29,30,31);
	EMinDam = EMinDam*(1+SynEMultiplicator/100);
	EMaxDam = EMaxDam*(1+SynEMultiplicator/100);
	EMinDam = EMinDam*DamModifier;
	EMaxDam = EMaxDam*DamModifier;
	stats = new Array();
	i = 0;
	stats[i++] = 'Mana cost: ' + FormulaManaCost(lvl,7,50,1);
	stats[i++] = 'Cast Delay: 1 Seconds';
	stats[i++] = 'Cold Duration: ' + NoNiHeCold(ELen) + ' Seconds';
	stats[i++] = 'Cold Damage: ' + FormulaFloor(EMinDam) + ' - ' + FormulaFloor(EMaxDam) + ' (ø' + FormulaAvg((EMinDam+EMaxDam)/2) + ')';
	stats[i++] = '[Synergy] Ice Bolt: +' + (inv_39*2) + '% Cold Damage (2% / Lvl)';
	return stats.join('\n');
}
//--------------------------------------------------------------
int calc_65(lvl) { //Cold Mastery
	stats = new Array();
	i = 0;
	stats[i++] = 'Enemy cold resistance: -' + FormulaLn(lvl,(20),(5)) + '%';
	return stats.join('\n');
}
