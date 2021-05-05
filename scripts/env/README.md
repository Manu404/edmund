These scripts are meant to get me up and ready from a debia clean install without dekstop ev.
Will install and configure: sudo, x11, i3, snap, vscodium, typora

from minimal debian, no desktop env:

```
wget https://github.com/Manu404/Edmund/scripts/env/setup_sudo.sh
wget https://github.com/Manu404/Edmund/scripts/env/setup_git.sh
wget +x ./setup*.sh
su
# Edit setup script with your regular user,
bash setup_sudo.sh <need reboot>
bash setup_git.sh
cd Edmund/scripts/env
./setup_all.sh
```
