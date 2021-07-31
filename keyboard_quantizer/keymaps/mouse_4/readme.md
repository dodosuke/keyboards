# The mouse keymap for keyboard_quantizer
Keyboard Quantizerを使ってマウスをQMK化するサンプル

```
    make keyboard_quantizer/rev3:mouse:flash
```

## 機能
このキーマップでは8ボタンマウスを対象に以下の機能を実現するサンプルです

- ボタン8によるレイヤー切り替え
  - レイヤ0ではボタン1からボタン5は通常通り動作します。ボタン6,7にはkeymap.cで任意の動作を設定できます
  - レイヤ1ではボタン1からボタン7に任意の動作を設定できます
- 簡易ジェスチャ機能
  - レイヤ1の状態でカーソルを左上、右上、左下、右下に移動してからレイヤ0に戻ったときに任意の動作を設定できます