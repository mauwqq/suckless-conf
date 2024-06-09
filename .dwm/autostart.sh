picom &
slstatus &
NetworkManager &
nextcloud &
nm-applet &
xautolock -time 10 -locker slock &
xidlehook \
  --not-when-fullscreen \
  --not-when-audio \
  --timer 540 \
    'brightnessctl set 10%' \
    '' \
  --timer 60 \
    'brightnessctl set 50% && systemctl suspend' \
    ''&
feh --bg-fill /home/anon/Nextcloud/Photos/background.png &
