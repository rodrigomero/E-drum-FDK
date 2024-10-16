
# E-drum
## Bateria Eletrônica

### Se usar um arduino com comunicacao usb ativa (usando o arduino leonardo no momento)
> O computador dectecta o arduino como um dispositivo MIDI normal, só abrir o VST e tocar.


### Se for usar um arduino sem connexao usb nativa (Ex: Arduino Uno)
Olhar a pasta docs pra diagramas de circuito e exemplos, instalar programas pra conversão de Serial->MIDI.

> O arduino manda o trigger pra o `Hairless` que le esse sinal e envia como MIDI para um controlador virtual criado pelo `LoopMIDI` 
 Piezo -> Arduino -> Hairless -> LoopMIDI -> VST

