# Git & GitHub Setup

A guide on how to setup a simple personal workflow using git and GitHub.

## A little Terminology

| Term| Definition |
|-----|------------|
| repo / repository | A folder usually in a remote location, similar to a folder in the cloud |
| terminal / bash | The command line interface of your OS. On Windows, usually accessed through Command Prompt app or Git Bash app |
| Git | A version control system — a program that tracks changes in files |
| GitHub | A cloud-based hosting platform for git repositories |

## Prerequisites

- Check that you have git with `git --version`. If you do not have git, please install it before continuing, along with Git Bash.
- Make a GitHub account at [github.com](https://github.com) if you do not have one already. Have GitHub open in your browser before continuing.
- Preferably use Git Bash as your terminal going forward.

## Initial Setup

1. Navigate to your desired folder in the terminal.
2. Initialize git:
   ```bash
   git init
   ```
3. Connect to the remote repository:
   ```bash
   git remote add origin https://github.com/RepositoryOwnerUsername/RepositoryName.git
   ```
4. Verify the connection (must show output — if empty, try connecting again):
   ```bash
   git remote -v
   ```
5. Pull your repository:
   ```bash
   git pull origin main
   ```
6. Make any changes to your tracked files.
7. Stage and commit your changes:
   ```bash
   git add .
   git commit -m "message"
   ```
8. **Generate a Personal Access Token (PAT) on GitHub:**
   - Go to: Profile picture → Settings → Developer Settings → Personal Access Tokens → Tokens (classic) → Generate new token (classic)
   - Set expiration to your preference (no expiration is fine for personal use)
   - Select the `repo` scope
   - Give the token a name in the **Note** field, then click **Generate token**
   - Copy the token and save it somewhere safe. **Do not share this token.** It acts as your password since GitHub no longer accepts your account password for authentication.

9. Set up auto-login so you aren't prompted every time:
    - go back to your terminal
   ```bash
   git config --global credential.helper store
   ```
10. Push your changes:
    ```bash
    git push origin main
    ```
    On first push you will be prompted to log in. Use your GitHub username and your PAT as the password. Future pushes will not prompt for credentials.

## Super Basic Day-to-Day Workflow

1. Pull latest changes before starting work to avoid conflicts:
   ```bash
   git pull origin main
   ```
2. Make your changes.
3. Stage and commit:
   ```bash
   git add .
   git commit -m "message"
   ```
4. Push:
   ```bash
   git push origin main
   ```
