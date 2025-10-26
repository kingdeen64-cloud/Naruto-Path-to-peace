# Naruto Road to World Peace (PSP Prototype)

This repository contains a **text-based PSP prototype** for *Naruto Road to World Peace*.
The first GitHub Actions build is the _text-only_ version so it's lightweight and easy to test.
Later commits can add graphics (stick-figure placeholders) and audio.

## What this package includes
- `src/main.c` : Text-based playable prototype. Naruto & Sasuke unlocked at start.
- `src/main_graphics.c` : Placeholder stub for future graphics-based build.
- `assets/` : Placeholder BMP sprites (simple color silhouettes) for later use.
- `Makefile` : Example Makefile that attempts to build using `pspsdk` (you may need to adapt flags for your runner).
- `.github/workflows/build.yml` : GitHub Actions workflow that tries to build the PBP and upload `EBOOT.PBP` as an artifact.
- `LICENSE` : MIT license.

## How to use
1. Upload the repository to GitHub (push to `NarutoFanFighter-PSP` repository).
2. Go to **Actions** → you should see the "Build PSP Game" workflow run.
3. If the build succeeds, download the artifact `EBOOT.PBP` and place it in your phone's `PSP/GAME/NarutoRoadToWorldPeace/EBOOT.PBP` to run in PPSSPP.

> NOTE: The GitHub Actions runner may not have `pspsdk` preinstalled. If the action fails at the build step, I can help you adapt the workflow — e.g., use a Docker container with PSPSDK preinstalled or run the build on a self-hosted runner. Tell me and I'll give an updated workflow.

## Controls (text demo)
- Cross / X: advance dialog / choose fight (in PPSSPP this is the CROSS button)
- Start: exit demo

## Save file
The game saves unlocks to `ms0:/PSP/SAVEDATA/NarutoRoadToWorldPeace/unlocked.dat`

## Next steps
- Replace placeholder assets with your own sprites.
- Add `src/main_graphics.c` gameplay features and enable graphical build in CI.
- I can create a GitHub Actions Docker image that contains PSPSDK and reliably builds for you if you'd like.

---
If you want me to update the workflow to use a Docker image that builds reliably on GitHub Actions, reply: **"Use Docker build workflow"**.
