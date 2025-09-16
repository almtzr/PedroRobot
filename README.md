# PedroRobot – Firmware

Firmware pour **Pedro**, un robot open-source et modulaire.
Ce dépôt contient le code embarqué permettant de contrôler Pedro via plusieurs modes de communication, ainsi que des fonctionnalités avancées comme l’enregistrement et la relecture de mouvements.

## ✨ Fonctionnalités

* 🎮 **Contrôle direct** – Commandes en temps réel via liaison série.
* 📶 **Bluetooth HC-05** – Contrôle sans fil simple et compatible avec de nombreuses applis mobiles.
* 📡 **Radio NRF24L01** – Communication robuste entre contrôleur et robot.
* 🌐 **Web Interface** – Interface en ligne pour piloter Pedro depuis un navigateur.
* 🔄 **Record & Replay** – Enregistre des séquences de mouvements et rejoue-les automatiquement.

## 📂 Structure du projet

* `src/` → Code source du firmware
* `config/` → Paramètres de communication et pins
* `examples/` → Exemples d’utilisation

## 🛠️ Installation

1. Clonez le repo :

   ```bash
   git clone https://github.com/almtzr/PedroRobot.git
   cd PedroRobot
   ```
2. Compilez et téléversez le firmware sur votre carte compatible (Arduino, ESP, etc.).
3. Sélectionnez le mode de contrôle souhaité (Direct, Bluetooth, NRF24L01, Web).

## 📑 Documentation et ressources

👉 Retrouvez la documentation complète, ainsi que les **fichiers STL pour l’impression 3D de Pedro**, dans le dépôt principal :
[Pedro – Documentation & STL](https://github.com/almtzr/Pedro)

## 🤝 Contribution

Les contributions sont les bienvenues !
N’hésitez pas à ouvrir une *issue* ou proposer une *pull request* pour améliorer le firmware.

## 📜 Licence

Projet open-source sous licence MIT.

---

