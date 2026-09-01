# PRINT — Material para Maratona de Programação

> Acervo pronto para impressão ICPC / OBI — CSES, AtCoder DP, templates, matemática e cadernos de referência.

[![C++](https://img.shields.io/badge/C%2B%2B-17-blue?style=flat-square)](https://en.cppreference.com/)
[![ICPC](https://img.shields.io/badge/ICPC-Notebook-red?style=flat-square)](#)
[![Status](https://img.shields.io/badge/status-pronto%20para%20impress%C3%A3o-brightgreen?style=flat-square)](#)

**English abstract:** This is a printable competitive programming notebook — curated CSES references by topic, AtCoder DP solutions, reusable C++ templates, and math sheets — organized for on-site contests (A4, ready to print).

---

## Sobre

Repositório `material-maratona` organizado para virar **caderno de prova**. Todo conteúdo está em PDF (pronto para levar impresso) + código-fonte C++ correspondente. Foco em **consulta rápida durante a prova**: enunciados condensados, limites, e truques por tópico.

---

## Estrutura

```
PRINT/
├── caderno_maratona_joao.pdf        # Caderno principal (base)
├── postila-UFMG-explicada.pdf       # Apostila UFMG comentada
├── error-list.pdf                   # Erros comuns & checklist
├── extra-code.pdf / extra-code/     # Templates genéricos (8)
│
├── cses/                            # CSES — 21 PDFs + 78 soluções
│   ├── cses-problems.pdf            # Compilado completo (3.9 MB)
│   ├── cses-2026-solutions.pdf      # Soluções comentadas 2026
│   ├── cses_2026_problems_tricks.pdf# Truques e sacadas 2026
│   ├── introductory.pdf ... trees.pdf (17 guias por tópico)
│   └── code/                        # 78 .cpp por categoria
│
├── atcoder/                         # AtCoder Educational DP Contest
│   ├── atcoder-dp-problems.pdf
│   ├── atcoder_dp_tricks.pdf / _template_2.pdf
│   ├── atcoder_dp_respostas.pdf
│   └── code/                        # 26 soluções DP clássicas
│
└── matematica/                      # 4 folhas de matemática
    ├── matematica_basica.pdf
    ├── combinatoria.pdf
    ├── trigonometria.pdf
    └── angulo-entre-vetores.pdf
```

Total: **32 PDFs** + **~112 arquivos C++**.

---

## Conteúdo em Detalhe

### 1) Cadernos Raiz

| Arquivo | Descrição |
|---|---|
| `caderno_maratona_joao.pdf` | Caderno principal — estruturas, grafos, strings, DP, geometria. Base para impressão. |
| `postila-UFMG-explicada.pdf` | Apostila da UFMG com explicações detalhadas — bom para estudo pré-prova. |
| `error-list.pdf` | Checklist de erros frequentes (overflow, limites, off-by-one, `long long`, `MOD`). |
| `extra-code.pdf` | Compilado dos templates de `extra-code/` em PDF único para impressão. |

### 2) CSES — Referência por Tópico

Cada PDF segue o padrão **ICPC reference**: enunciado condensado (1s / 512 MB), entrada/saída e limites — sem exemplos, para caber impresso.

| PDF | Tópico | Problemas cobertos |
|---|---|---|
| `introductory.pdf` | Introdução | Two Knights, Trailing Zeros, Apple Division, Grid Paths, etc. |
| `sorting.pdf` | Sorting & Searching | Towers, Stick Lengths, Array Division, Concert Tickets, Playlist, etc. |
| `dymanic.pdf` | Dynamic Programming | Dice Combinations, Coin Combinations, Grid Paths I, Edit Distance, etc. |
| `graphs.pdf` + `graphs` cont. | Graph Algorithms | Counting Rooms, Labyrinth, Flight Discount, Cycle Finding, Building Roads, etc. |
| `range-queries.pdf` | Range Queries | Hotel Queries, Salary Queries, Subarray Sum Queries, Forest Queries, etc. |
| `trees.pdf` | Tree Algorithms | Subordinates, Tree Matching/Diameter, LCA, Counting Paths, Fixed-Length Paths, etc. |
| `mathematics.pdf` | Mathematics | Binomial Coefficients, Exponentiation, Fibonacci, Graph Paths, etc. |
| `string.pdf` | String Algorithms | Word Combinations, String Matching, Finding Borders, Palindrome Queries, etc. |
| `geometry.pdf` | Geometry | Intersection Points, Area of Rectangles, Polygon Area, Convex Hull, etc. |
| `advanced_techniques.pdf` | Advanced Techniques | Meet in the Middle, Hamming Distance, Reachable Nodes, etc. |
| `sliding.pdf` | Sliding Window | Sliding Window Median/Cost/Mex/Sum, Advertisement, etc. |
| `interactive.pdf` | Interactive | Hidden Integer/Permutation, K-th Highest Score, Colored Chairs, etc. |
| `bitwise.pdf` | Bitwise Operations | Counting Bits, Maximum Xor Subarray/Subset, SOS Bit Problem, etc. |
| `construction.pdf` | Construction | Inverse Inversions, Chess Tournament, Grid Path Construction, etc. |
| `advanced_graph.pdf` | Advanced Graph | Nearest Shops, Prüfer Code, Graph Girth, MST Edge Check, etc. |
| `counting.pdf` | Counting | Counting Permutations, Grid Paths II, Counting Reorders, etc. |
| `additional_problems_i.pdf` | Additional I | Advertisement, Sorting Methods, Bit Inversions, Pyramid Array, etc. |
| `additional_problems_ii.pdf` | Additional II | Maximum Building II, Stick Divisions, Two Stacks Sorting, etc. |
| `cses-problems.pdf` | **Compilado total** | Todos os CSES em um único PDF (referência rápida). |
| `cses_2026_problems_tricks.pdf` | Truques 2026 | Sacadas e padrões por problema (estudo). |
| `cses-2026-solutions.pdf` | Soluções 2026 | Soluções comentadas. |

<details>
<summary><b>78 soluções em <code>cses/code/</code> por categoria</b></summary>

| Categoria | Qtde | Exemplos |
|---|---:|---|
| Additional Problems I | 14 | `beautiful_permutation_II.cpp`, `distinct_values_splits.cpp` |
| Additional Problems II | 15 | `two_stacks_sorting.cpp`, `maximum_building_II.cpp` |
| Advanced Graph Problems | 13 | `nearest_shops.cpp`, `mst_edge_check.cpp`, `prufer_code.cpp` |
| Counting Problems | 10 | `counting_reorders.cpp`, `filled_subgrid_count_I.cpp` |
| Interactive Problems | 6 | `hidden_integer.cpp`, `colored_chairs.cpp` |
| Bitwise Operations | 5 | `sos_bit_problem.cpp`, `k_subset_xors.cpp` |
| Construction Problems | 5 | `third_permutation.cpp`, `filling_trominos.cpp` |
| Tree Algorithms | 2 | `fixed_length_paths_I.cpp`, `fixed_length_paths_II.cpp` |
| Advanced Techniques, Dynamic, Geometry, Graph, Mathematics, Range, Sliding, String | 1 cada | `corner_subgrid_check.cpp`, `minimal_grid_path.cpp`, etc. |

</details>

### 3) AtCoder — Educational DP Contest (26 problemas)

Coleção completa do **AtCoder DP Contest** com 4 PDFs e código:

**PDFs:** `atcoder-dp-problems.pdf` · `atcoder_dp_tricks.pdf` · `atcoder_dp_tricks_template_2.pdf` · `atcoder_dp_respostas.pdf`

**Códigos em `atcoder/code/` (26):**

| Arquivo | Clássico | Técnica |
|---|---|---|
| `frog.cpp`, `frog2.cpp`, `frog3.cpp` | Frog 1/2/3 | DP simples + Convex Hull Trick |
| `vacation.cpp` | Vacation | DP 3 estados |
| `knapsack1.cpp`, `knapsack2.cpp` | Knapsack 1/2 | Peso vs. valor |
| `lcs.cpp` | LCS | DP 2D + reconstrução |
| `longest_path.cpp` | Longest Path (DAG) | Toposort DP |
| `grid1.cpp`, `grid2.cpp` | Grid 1/2 | Grid DP + obstáculos |
| `coins.cpp` | Coins | DP probabilístico |
| `sushi.cpp` | Sushi | DP com expectativa |
| `stones.cpp` | Stones | Jogo minimax |
| `deque.cpp` | Deque | Interval DP |
| `slimes.cpp` | Slimes | Interval DP (merge) |
| `matching.cpp` | Matching | Bitmask DP |
| `independent-set.cpp` | Independent Set | Tree DP |
| `flowers.cpp` | Flowers | BIT / SegTree DP |
| `walk.cpp` | Walk | Matrix exponentiation |
| `digit-sum.cpp` | Digit Sum | Digit DP |
| `permutation.cpp` | Permutation | DP permutação |
| `grouping.cpp` | Grouping | Subset DP `O(3^n)` |
| `candies.cpp`, `tower.cpp`, `subtree.cpp`, `intervals.cpp` | Extras | DP variados |

### 4) `extra-code/` — Templates Prontos (8)

Templates de prova, testados e comentados:

| Template | Uso |
|---|---|
| `segment-tree.cpp` | SegTree genérica (SUM/MAX/MIN/GCD/XOR/MULT) + lazy ADD/SET — 270 linhas, plug-and-play |
| `segtree_lazy_maxq_soma-update.cpp` | Lazy max + soma |
| `kosaruju.cpp` | Kosaraju — SCC |
| `bfs_grid.cpp` | BFS em grade |
| `knapsack-valor-recupecao.cpp` | Mochila com reconstrução |
| `subset_sum_com_uma_determinada_quantidade_de_elementos.cpp` | Subset sum com cardinalidade |
| `problema_iterativo_binary_search.cpp` | Busca binária iterativa |
| `problema_two_pointers_mais_numero_de_substrings.cpp` | Two pointers — contagem de substrings |

### 5) `matematica/` — Folhas de Matemática

| PDF | Conteúdo |
|---|---|
| `matematica_basica.pdf` | Bases, razões, equações |
| `combinatoria.pdf` | Permutação, combinação, stars and bars, Catalan, inclusão-exclusão — com intuição de quando usar |
| `trigonometria.pdf` | Identidades, lei dos senos/cossenos |
| `angulo-entre-vetores.pdf` | Produto escalar, ângulo, projeção |


---

## Contribuindo

```bash
git clone https://github.com/thehouseisonfire/material-maratona.git
cd material-maratona
# adicione seu PDF em cses/ ou template em extra-code/
# mantenha o padrão: código com #include <bits/stdc++.h> e main() mínimo
git add .
git commit -m "add: <tópico> - <problema>"
```
