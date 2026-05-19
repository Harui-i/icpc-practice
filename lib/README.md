# Harui's memo

[![Actions Status](https://github.com/Harui-i/library/workflows/verify/badge.svg)](https://github.com/Harui-i/library/actions)

[![GitHub Pages](https://img.shields.io/static/v1?label=GitHub+Pages&message=+&color=brightgreen&logo=github)](https://harui-i.github.io/library/) 

めちゃめちゃ味気ない名前してるので、いつか"Harui's library"とか
" Haruis Bibliothek"みたいな名前に変えたいね！

## Verify

検証用の Python 依存は `pyproject.toml` で管理しています。

```bash
scripts/verify.sh
```

`oj-verify` に引数を渡す場合は、そのまま続けて指定できます。

```bash
scripts/verify.sh all --jobs 20
```
