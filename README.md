# Let's Vertical
詳しくは[こちら](https://ynakano1127.hatenablog.com/entry/2021/12/25/211410)  

OpenType形式のフォントファイルを読み込み，縦書きするソースコードです．  FreeTypeのみの依存で実現できるよう目指しました．  
プロジェクト内に`NotoSansCJKjp-Thin.otf`やら`NotoSerifJP-Regular.otf`やらを入れ，実行してください．  
`Image.h`,`Image.cpp`はかなり適当に移植したので，2重解放やらなんやらが発生する確率大です．  
IDEはQtCreatorを使いました．