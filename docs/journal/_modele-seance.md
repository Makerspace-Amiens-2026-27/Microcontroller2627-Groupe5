---
layout: default
title: "2026-11-18 : début du projet microcontrôleur"
parent: Prénom Nom
grand_parent: Journal de bord
---

# 2026-11-18 : début du projet microcontrôleur

**Séance :** planifiée
**Durée :** 1 h 30

## Mise en place de l'environnement

Nous avons téléchargé et installé **VS Code** et **PlatformIO**, puis vérifié la toolchain en faisant clignoter la LED de l'**ESP32-S3**. Le test a fonctionné : l'environnement de développement est donc opérationnel.

## Lecture des données avec Teleplot

Nous avons essayé de lire les données du port série avec **PlatformIO** et **Teleplot**. Les informations sont bien reçues, mais la courbe ne s'affiche pas.

## Bilan et suite

- ✅ Environnement VS Code + PlatformIO installé
- ✅ Toolchain validée (clignotement de la LED de l'ESP32-S3)
- ❌ Affichage des courbes Teleplot : données reçues mais pas de tracé, à débugger