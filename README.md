# Unreal-Engine-5
Files in C++ that make up the functional base of different mechanics in a game

The code is divided into different sections.

The Breakable section is based on objects that we can destroy by implementing a force on its structure.

The Characters section is divided into BaseCharacter, which is the parent class for the rest of the characters we make, GAnimInstance is used to create Animation Blueprints for the characters, and GreystoneCharacter has all the methods of the character we play with.

In the Components section we have defined the class that will be used to create the Widget with the different attributes of the characters, life, stamina, mana among others.

In the Enemy section we define a child of BaseCharacter that will be used to create different enemies with their attributes, methods, among others.

In the Interfaces section we have HitInterfaces that is based on an interface to implement the fact of receiving damage or receiving it.

PickupInterface is based on implementing the pickup of objects, souls, anima

In the Items section we have several classes.

Weapon's:
It involves all the operation of the weapons and their hit box, collisions, effects, equip, unequip.

The item class involves any object that we can pick up, it will be the parent of the Soul and Treasure child classes, both are objects with their respective animations.

The Pawns section includes the Bird class that is based on the logical operation of programming a flying bird.

And the Widget section finally involves everything related to the display of life, stamina and the fact of being attachable to the characters
