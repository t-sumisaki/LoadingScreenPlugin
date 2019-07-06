# LoadingScreenPlugin

シンプルな非同期LoadingScreenを追加します  
EpicGamesのActionRPG内にあるLoadingScreenの仕組みをベースにプラグイン化しました

## 導入方法
`[ProjectFolder]/Plugins` 内に配置してビルドしてください



## 使い方

- ゲーム起動時
  ゲーム起動時に3秒間LoadingScreenが表示されます
  
- レベル移動時
  レベル移動前に `PlayLoadingScreen` ノードを使用してください
  - bPlayerUntilStopped
    -> 移動後に `StopLoadingScreen` ノードを使用するまでLoadingScreenを表示し続けます
  - PlayTime
    -> bPlayerUntilStoppedがFalseのとき、ここに指定された秒数分LoadingScreenを表示します


## 設定変更
ProjectSettings > Plugins > LoadingScreenに、カスタマイズ用の設定があります

- LoadingScreenTexture
  -> ローディングスクリーンの中央部分に配置されるTexture
- TextureSize
  -> LoadingScreenTextureのサイズを指定
- BackgroundTintColor
  -> 背景色を指定
  

## 予定
- [ ] ゲーム起動時の挙動カスタマイズ用の設定項目追加
- [ ] BPプロジェクト向けのBinaryリリース
