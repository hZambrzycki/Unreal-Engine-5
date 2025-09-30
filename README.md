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


> If your folders differ, keep class names consistent and include headers accordingly.

---

## 🚀 Getting started

### Requirements
- **Unreal Engine 5.x** (C++ project)
- **Visual Studio 2022** (Windows) or **Xcode** (macOS)
- C++ toolchain compatible with UE5

### Install (add to an existing UE5 C++ project)
1. Create (or use) a **UE5 C++** project.  
2. Copy these headers/sources into `Source/<YourProject>/` keeping the folder grouping above.  
3. Add module includes if needed in `<YourProject>.Build.cs`.  
4. **Regenerate project files** (right-click the `.uproject`).  
5. Build from your IDE and launch the editor.

---

## 🧩 Usage notes & extension points

- **Hit / Damage flow**  
  Implement `HitInterface` on actors that can take damage; weapons call the interface when their hit box overlaps a valid target.

- **Pick-ups**  
  Implement `PickupInterface` to grant resources (e.g., Souls/Treasure) on overlap; throttle via cooldown or once-per-actor flags.

- **Weapons**  
  Use weapon equip/unequip methods to attach meshes to sockets; enable collision only during attack windows (notify-driven).

- **Attributes & UI**  
  The attribute component exposes getters/setters for **health**, **stamina**, **mana**; bind the Widget to update bars and text.

- **Breakables**  
  Spawn breakable actors and apply forces (e.g., `AddImpulse`/`RadialForce`) on impact to fracture/destroy pieces.

- **Animation**  
  `GAnimInstance` serves as the ABP logic layer (movement states, montage sections, notifies for enabling weapon collision, etc.).

- **Debug**  
  Include `DebugMacros.h` to toggle on-screen logs / draw helpers while iterating.

> These systems are intentionally decoupled so you can replace pieces (e.g., your own AttributeComponent or different weapon tracing).

---

## 🧪 Testing in-editor

- Create a simple test **Level**: place a `GreystoneCharacter` PlayerStart, an `Enemy`, a `Weapon` pickup, a couple of `Breakables`, and a **HUD** Widget.  
- Validate loops:
  - Weapon equip → attack → hit interface triggers → enemy health decreases  
  - Pickup Soul/Treasure → UI updates  
  - Breakable receives force → destroys properly  
  - Bird pawn pathing (if placed) behaves as expected

---

## 📦 Roadmap ideas

- AIController/BT for `Enemy` (patrol, chase, attack)  
- Damage types (physical/elemental), resistances & status effects  
- Save/Load for attributes & inventory  
- Network replication passes for combat & pickups  
- DataAssets for tuning items and characters

---

## 📄 License

MIT (recommended). Add a `LICENSE` file if you plan to share/extend publicly.

---

## 🙌 Author

Built by **Hubert Zambrzycki** — C++/UE5 developer.  
Focused on clean, reusable gameplay foundations for rapid iteration.


This repository is a code pack, intended to live under a UE5 project’s `Source/<YourProject>/`:

