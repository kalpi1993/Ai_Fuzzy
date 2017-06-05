/* J.D.K.P Jayasinghe IT14022548*/

#include <FuzzyRule.h>
#include <FuzzyComposition.h>
#include <Fuzzy.h>
#include <FuzzyRuleConsequent.h>
#include <FuzzyOutput.h>
#include <FuzzyInput.h>
#include <FuzzyIO.h>
#include <FuzzySet.h>
#include <FuzzyRuleAntecedent.h>

/* Instantiating Objects*/
Fuzzy* fuzzy = new Fuzzy();

void setup(){
 Serial.begin(9600);

 /*Creating a FuzzyInput distance*/
 FuzzyInput* distance = new FuzzyInput(1);// With its ID in param

 // Creating the FuzzySet 
 
 FuzzySet* small = new FuzzySet(0, 20, 20, 40); // Small distance
 distance->addFuzzySet(small); // Add FuzzySet small to distance
 FuzzySet* safe = new FuzzySet(30, 50, 50, 70); // Safe distance
 distance->addFuzzySet(safe); // Add FuzzySet safe to distance
 FuzzySet* big = new FuzzySet(60, 80, 80, 80); // Big distance
 distance->addFuzzySet(big); // Add FuzzySet big to distance

 fuzzy->addFuzzyInput(distance); // Add FuzzyInput to Fuzzy object

 /* Creating FuzzyOutput velocity*/
 FuzzyOutput* velocity = new FuzzyOutput(1);// With its ID in param

 // Creating FuzzySet to FuzzyOutput velocity
 FuzzySet* slow = new FuzzySet(0, 10, 10, 20); // Slow velocity
 velocity->addFuzzySet(slow); // Add FuzzySet slow to velocity
 FuzzySet* average = new FuzzySet(10, 20, 30, 40); // Average velocity
 velocity->addFuzzySet(average); // Add FuzzySet average to velocity
 FuzzySet* fast = new FuzzySet(30, 40, 40, 50); // Fast velocity
 velocity->addFuzzySet(fast); // Add FuzzySet fast to velocity

 fuzzy->addFuzzyOutput(velocity); // Add FuzzyOutput to Fuzzy object

 /*Fuzzy rules*/
 
 FuzzyRuleAntecedent* ifDistanceSmall = new FuzzyRuleAntecedent(); // Instantiating 
 ifDistanceSmall->joinSingle(small); // Adding corresponding FuzzySet1 
 FuzzyRuleConsequent* thenVelocitySlow = new FuzzyRuleConsequent(); // Instantiating
 thenVelocitySlow->addOutput(slow);// Adding corresponding FuzzySet2 
 // Instantiating a FuzzyRule object
 FuzzyRule* fuzzyRule01 = new FuzzyRule(1, ifDistanceSmall, thenVelocitySlow); 
 
 fuzzy->addFuzzyRule(fuzzyRule01); // Adding Fuzzy Rules
 
 FuzzyRuleAntecedent* ifDistanceSafe = new FuzzyRuleAntecedent(); 
 ifDistanceSafe->joinSingle(safe); 
 FuzzyRuleConsequent* thenVelocityAverage = new FuzzyRuleConsequent(); 
 thenVelocityAverage->addOutput(average); 
 
 FuzzyRule* fuzzyRule02 = new FuzzyRule(2, ifDistanceSafe, thenVelocityAverage); 
 
 fuzzy->addFuzzyRule(fuzzyRule02); // Adding FuzzyRules
 
 
 FuzzyRuleAntecedent* ifDistanceBig = new FuzzyRuleAntecedent(); 
 ifDistanceBig->joinSingle(big); 
 FuzzyRuleConsequent* thenVelocityFast = new FuzzyRuleConsequent(); 
 thenVelocityFast->addOutput(fast);
 
 FuzzyRule* fuzzyRule03 = new FuzzyRule(3, ifDistanceBig, thenVelocityFast); 
 
 fuzzy->addFuzzyRule(fuzzyRule03); 
}

void loop(){
 float dist = getDistanceFromSonar(); 
 
/*inputs value, passing its ID and value*/
fuzzy->setInput(1, dist); 
 /*fuzzification*/
 fuzzy->fuzzify(); 
 /* Defuzzification */
 float output = fuzzy->defuzzify(1);

 setRobotSpeed(output);

 delay(100);
}
