


# UE5 Skateboarding Prototype

![skateboard-prototype](https://github.com/user-attachments/assets/21e8365f-88a2-4296-acf4-9e073abd7cf6)

A skateboarding gameplay prototype developed in Unreal Engine 5 as part of a technical assessment.  
The project focuses on movement feel, traversal-based scoring, and clean UI architecture.

## 🎮 Controls

- **W** → Accelerate / Push  
- **S** → Brake  
- **A / D** → Turn  
- **Mouse** → Camera  
- **Space** → Jump  

---

## ⚙️ Systems Overview

### 🛹 Locomotion System
- Hybrid movement using Character Movement Component with manual velocity control  
- Momentum-based acceleration and custom drag system  
- Speed-dependent turning with carving behavior  
- Designed to prioritize responsiveness and gameplay feel  

---

### 🧱 Traversal Scoring System
- Scores are awarded for interacting with obstacles while airborne  
- Obstacle detection via periodic sweep checks  
- Scoring is validated on landing to ensure intentional actions  
- Combo system with multiplier and time window  
- Per-obstacle cooldown to prevent repeated scoring  

---

### 🖥️ UI (MVVM)
- Implemented using Unreal Engine MVVM framework  
- ViewModel exposes score, combo multiplier, and timer  
- Field Notify used for automatic UI updates  
- Derived values (e.g. combo percentage) handled in ViewModel  
- Game Instance subsystem manages ViewModel lifecycle  

---

## 🧠 Technical Highlights

- Data-driven configuration using Developer Settings  
- Custom collision channel for obstacle detection  
- Modular design using Actor Components and Interfaces  
- Debug tools implemented via console variables (CVars)  
- Use of Enhanced Input for scalable input handling  

> The input system was designed with scalability in mind and can be extended to a Gameplay Ability System (GAS)-based approach if needed.

---

## 🧩 Design Considerations

- Systems were designed to be modular and easily extensible (e.g., obstacle scoring via interface)
- Data-driven configuration allows gameplay tuning without code changes
- Movement system avoids full physics simulation to maintain control and iteration speed
- Movement would require client prediction and reconciliation for multiplayer adaptation due to manual velocity handling
- Scoring system is event-driven and can be validated server-side for consistency

---

---

## 📂 Repository Contents

This repository contains the **C++ source and project configuration only**. The `Content/` folder (marketplace/sample art, Blueprints and the level) is not included, so the project compiles but won't run as-is. The GIF above shows it in action.

| Area | Where to look |
|---|---|
| Locomotion (momentum, drag, carving) | `Source/NgpUnrealDevTask/*/Core/NGPPlayerCharacter.*` |
| Traversal scoring, combos, cooldowns | `Source/NgpUnrealDevTask/*/Systems/TraversalScoring/NGPTraversalScoreComponent.*` |
| Obstacle contract (interface + actor) | `Source/NgpUnrealDevTask/*/Systems/TraversalScoring/NGPObstacle*` |
| Data-driven tuning | `Source/NgpUnrealDevTask/*/Systems/TraversalScoring/NGPTraversalDeveloperSettings.*` |
| MVVM ViewModel + lifecycle subsystem | `Source/NgpUnrealDevTask/*/UI/` |
| Debug CVars | `Source/NgpUnrealDevTask/*/Helpers/NGPCvarManager.*` |

Built with Unreal Engine 5.7.

---

## 📌 Notes

This prototype focuses on core gameplay systems and iteration speed.  
Animation polish, game flow (menus, restart), and additional features were intentionally kept minimal.

---

## ⏱️ Time Investment

- Project setup, Git LFS, asset import: 1h  
- Locomotion system: 3h  
- Animation setup: 1h  
- Traversal scoring system: 3h  
- UI (MVVM): 3h  
- Level design: 2h  

**Total:** ~14 hours
