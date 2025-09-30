# 🎮 Unreal Engine 5 – Gameplay Systems (C++)

A collection of **Unreal Engine 5 gameplay systems in C++** that form the functional base of different game mechanics: characters, items, combat touchpoints (hit boxes & damage), breakable actors, pick-ups, UI widgets for attributes, and more.  
> Original goal: keep these systems modular so they can be dropped into any UE5 C++ project as a starting point.  

---

## ✨ What’s inside

> High-level modules as described in this repo’s docs and sources.

- **Breakables**  
  Actors you can destroy by applying forces to their structure (e.g., radial impulses). Useful for props with physical reactions. :contentReference[oaicite:1]{index=1}

- **Characters**  
  - `BaseCharacter`: parent class with common movement, attributes, and hooks for combat.  
  - `GreystoneCharacter`: the playable character implementing the specific abilities/inputs.  
  - `GAnimInstance`: `UAnimInstance` used to drive Animation Blueprints for state-based animation logic. :contentReference[oaicite:2]{index=2}

- **Enemy**  
  Child of `BaseCharacter` with enemy-specific attributes and behaviors (damage reception, attacks, etc.). :contentReference[oaicite:3]{index=3}

- **Interfaces**  
  - **HitInterface**: receiving & processing hit/damage events.  
  - **PickupInterface**: handling object pick-ups such as **Souls** or **Treasure**. :contentReference[oaicite:4]{index=4}

- **Items**  
  - `Item`: base class for pickable objects.  
  - `Weapon`: equips/unequips, manages collisions / hit boxes and VFX/SFX triggers.  
  - `Soul` & `Treasure`: item types with their own animations/feedback. :contentReference[oaicite:5]{index=5}

- **Components & UI**  
  Attribute/Stats component (health, stamina, mana) + **Widget/HUD** that displays these values and attaches to characters. :contentReference[oaicite:6]{index=6}

- **Pawns**  
  `Bird`: logic for a flying pawn (movement loop / steering). :contentReference[oaicite:7]{index=7}

- **Debug utilities**  
  `DebugMacros.h`: helper macros for quick on-screen logs and draw-debug calls during gameplay.

> Language breakdown on GitHub shows **C++ ~95%** (plus minor C). :contentReference[oaicite:8]{index=8}

---

## 🧱 Project structure (typical UE5 layout)

This repository is a code pack, intended to live under a UE5 project’s `Source/<YourProject>/`:

