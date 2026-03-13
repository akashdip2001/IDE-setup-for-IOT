# Windows Development Environment Setup Guide

This guide helps you set up your Windows laptop for development after a fresh reset.

## 1. Install Oh My Posh

```powershell
winget install JanDeDobbeleer.OhMyPosh
```

## 2. Set PowerShell Execution Policy

```powershell
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
```

## 3. Configure PowerShell Profile

Create/edit your PowerShell profile:

```powershell
notepad $PROFILE
```

If the file doesn't exist, create it first:

```powershell
New-Item -Path $PROFILE -Type File -Force
notepad $PROFILE
```

Add this line to the file:

```powershell
oh-my-posh init pwsh | Invoke-Expression
```

Save and close the file.

## 4. Restart Terminal

Close and reopen your terminal. Oh My Posh should now load automatically.

## 5. (Optional) Change Theme

To use a specific theme:

```powershell
oh-my-posh init pwsh --config "$env:POSH_THEMES_PATH\paradox.json" | Invoke-Expression
```

Update your `$PROFILE` with the theme if you like it.

## Additional Development Tools

### Install Python (if needed)

```powershell
winget install Python.Python.3.10
```

### Install Git

```powershell
winget install Git.Git
```

### Install VS Code

```powershell
winget install Microsoft.VisualStudioCode
```

### Install Pipenv

```powershell
pip install --user pipenv
```

## Troubleshooting

**Issue:** Scripts won't run due to execution policy
**Solution:** Run `Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser`

**Issue:** Oh My Posh doesn't load in new terminals
**Solution:** Ensure the init command is in your `$PROFILE` file

**Issue:** Profile location unknown
**Solution:** Run `echo $PROFILE` to see the path
