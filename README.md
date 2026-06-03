# 🛰️ Braço Robótico de Coleta de Amostras — *Docking & Retrieval*

**Global Solution 2026 · Indústria Espacial** — FIAP · Engenharia de Software · 4º Ano (Presencial)
**Disciplina:** Project-Based Maker Lab (PBML)

> Braço robótico de 2 graus de liberdade para **captura de amostras em microgravidade**, controlado por comandos de teclado via Monitor Serial. Um Arduino Uno aciona **2 servomotores** (a articulação do braço e a garra) e um **LED de status**. O circuito é simulado no Tinkercad e as peças mecânicas são modeladas de forma paramétrica em OpenSCAD.

---

## 👥 Integrantes

| Nome | RM |
|------|----|
| Guilherme Rocha Bianchini | RM97974 |
| Nikolas Rodrigues Moura dos Santos | RM551566 |
| Pedro Henrique Pedrosa Tavares | RM97877 |
| Rodrigo Brasileiro | RM98952 |
| Thiago Jardim de Oliveira | RM551624 |

**Grupo:** _`TPGN - TechPulse Global Network`_

---

## 🔗 Links da entrega

| Recurso | Link |
|---------|------|
| 🔌 Simulador do circuito (Tinkercad — **público**) | [_`https://www.tinkercad.com/things/aPYhfb0wO8s/editel?returnTo=%2Fusers%2F0ihK8cLdiOE&sharecode=gYKTYNBTAVL7AkND236sMprZ-sYblSV4BKXsZEcPdEs`_ ](https://www.tinkercad.com/things/aPYhfb0wO8s/editel?returnTo=%2Fusers%2F0ihK8cLdiOE&sharecode=gYKTYNBTAVL7AkND236sMprZ-sYblSV4BKXsZEcPdEs)|

---

## 🗂️ Estrutura do repositório

```
GS2026-PBML-Braco-Robotico/
├── src/
│   └── braco_robotico.ino        # firmware do Arduino (controle serial dos servos)
├── model/
│   ├── garra.scad                # modelo 3D paramétrico — a MÃO (garra de engrenagens)
│   ├── braco_robotico.scad       # modelo 3D paramétrico — o BRAÇO completo (importa garra.scad)
│   ├── garra.stl                 # exportação universal da garra        (gerar no OpenSCAD)
│   └── braco_robotico.stl        # exportação universal do braço        (gerar no OpenSCAD)
├── images/
│   ├── circuito_tinkercad.png    # print do circuito simulado           (adicionar)
│   ├── serial_monitor.png        # print do Monitor Serial em operação   (adicionar)
│   ├── braco_3d_lateral.png      # vista lateral do braço (validação)
│   └── garra_layout_verificacao.png  # vista de topo da garra (validação)
└── README.md
```

---

## 🎮 Guia de operação (comandos do Monitor Serial)

Abra o **Monitor Serial** a **9600 baud** (terminação *Nova linha*). Digite um caractere e Enter:

| Comando | Ação | Servo afetado |
|:---:|------|------|
| `U` | **Up** — sobe a articulação do braço | Servo 1 (ombro) |
| `D` | **Down** — desce a articulação do braço | Servo 1 (ombro) |
| `O` | **Open** — abre a garra | Servo 2 (mão) |
| `C` | **Close** — fecha a garra (captura a amostra) | Servo 2 (mão) |
| `H` | **Home** — retorna à posição neutra | Ambos |
| `?` | **Ajuda** — lista os comandos | — |

**LED de status:** aceso = garra **fechada** (segurando amostra); pisca na inicialização e em comando inválido.

### Sequência de demonstração sugerida
`?` → `O` (abre) → `U` `U` (sobe) → `C` (fecha = captura) → `D` (desce com a amostra) → `O` (solta) → `H` (home).

---

## 🔧 Especificações técnicas

### Circuito (Tinkercad)
- **Controlador:** Arduino Uno R3
- **Atuadores:** 2× micro servo **SG90 (9g)** — articulação (U/D) + garra (O/C)
- **Sinalização:** 1× LED de status + resistor **220 Ω**
- **Alimentação dos servos:** **fonte de bancada 5 V (ou 6 V)** — *não* o pino 5V do Arduino
- **Terra comum:** GND do Arduino ligado ao trilho da fonte (referência do PWM)

### Pinagem do Arduino
| Pino | Conexão |
|:---:|---------|
| `~D9` | Sinal do Servo 1 — articulação (U/D) |
| `~D10` | Sinal do Servo 2 — garra (O/C) |
| `D7` | LED de status (via resistor 220 Ω) |
| `GND` | Terra comum: fonte + servos + LED |
| `5V` | *Não usar para os servos* (apenas lógica) |

---

## 🖨️ Modelos 3D (OpenSCAD — paramétricos)

**Software de modelagem:** [OpenSCAD](https://openscad.org). Todas as dimensões são **variáveis** editáveis no topo de cada arquivo (e via *Customizer*), prevendo o encaixe dos servos SG90 de 9g.

### `model/garra.scad` — a mão
Garra de **engrenagens gêmeas**: um único servo aciona o *dedo motor*, e o *dedo seguidor* engrena nele e fecha de forma simétrica. As pontas têm um **berço côncavo** que abraça uma amostra esférica.

### `model/braco_robotico.scad` — o braço completo (2-DOF)
Importa o `garra.scad` e adiciona a **base + ombro + elo**. O servo 1 levanta/abaixa o elo (U/D) e, no punho, o servo 2 aciona a garra (O/C). Faixa útil validada: **-20° (captura no plano) a +80° (recolhido)**.


## ▶️ Como reproduzir

1. **Circuito:** abra o projeto no Tinkercad (link acima), confirme a fonte em 5–6 V e o terra comum, e clique em *Start Simulation*.
2. **Firmware:** o código de `src/braco_robotico.ino` já está carregado no Arduino do simulador (editor em modo *Text*). Para uso real, abra-o na Arduino IDE (usa a biblioteca padrão `Servo.h`).
3. **Operação:** abra o Monitor Serial (9600 baud) e use os comandos da tabela acima.
4. **Peças 3D:** abra os `.scad` no OpenSCAD para visualizar/ajustar/exportar.

---

## 🌍 Conexão com a Indústria Espacial e ODS

Sistema de **docking & retrieval** — manipulação e coleta de cargas/amostras em ambiente de microgravidade, base tecnológica para captura de detritos orbitais, coleta de regolito e manutenção de satélites. Conecta-se ao **ODS 9** (Inovação e Infraestrutura).

---

*FIAP · Global Solution 2026 · Indústria Espacial · ESPW 4º Ano · Project-Based Maker Lab*


