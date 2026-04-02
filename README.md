# UE5 Skateboarding Prototype

<img width="1936" height="1048" alt="ScreenShot00001" src="https://github.com/user-attachments/assets/cf8b1a73-35fc-4227-8558-91ddced1ac87" />

A skateboarding gameplay prototype developed in Unreal Engine 5 as part of a technical assessment.  
The project focuses on movement feel, traversal-based scoring, and clean UI architecture.

---

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
