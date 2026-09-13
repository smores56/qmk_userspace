COMBO_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes

# promicro_to_proton_c forces AUDIO_ENABLE=yes; the board has no speaker and
# audio's timers compete with the bitbang split serial on ARM.
AUDIO_ENABLE = no
