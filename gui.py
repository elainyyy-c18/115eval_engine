import tkinter as tk
from tkinter import ttk
import subprocess
import sys
import re

class CalculusGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("🧮 C-Powered Advanced Calculus Engine")
        self.root.geometry("550x450")
        self.root.resizable(False, False)
        
        # 標題
        lbl_title = ttk.Label(root, text="Multivariable Calculus Engine", font=("Segoe UI", 16, "bold"))
        lbl_title.pack(pady=10)

        # 建立分頁 (Tabs)
        self.notebook = ttk.Notebook(root)
        self.notebook.pack(fill="both", expand=True, padx=20, pady=5)

        # 建立各個分頁
        self.tab_basic = ttk.Frame(self.notebook)
        self.tab_diff = ttk.Frame(self.notebook)
        self.tab_int1 = ttk.Frame(self.notebook)
        self.tab_int2 = ttk.Frame(self.notebook)
        self.tab_int3 = ttk.Frame(self.notebook)

        self.notebook.add(self.tab_basic, text="一般計算")
        self.notebook.add(self.tab_diff, text="微分 (diff)")
        self.notebook.add(self.tab_int1, text="一重積分")
        self.notebook.add(self.tab_int2, text="二重積分")
        self.notebook.add(self.tab_int3, text="三重積分")

        self.build_basic_tab()
        self.build_diff_tab()
        self.build_int1_tab()
        self.build_int2_tab()
        self.build_int3_tab()

        # 共用的計算按鈕與結果顯示區
        frame_bottom = ttk.Frame(root)
        frame_bottom.pack(fill="x", padx=20, pady=15)

        btn_calc = ttk.Button(frame_bottom, text="🚀 執行 C 語言核心計算", command=self.calculate)
        btn_calc.pack(fill="x", ipady=8)

        frame_result = ttk.Frame(frame_bottom)
        frame_result.pack(fill="x", pady=10)
        
        ttk.Label(frame_result, text="運算結果: ", font=("Segoe UI", 12, "bold")).pack(side="left")
        self.lbl_result = ttk.Label(frame_result, text="---", font=("Consolas", 16, "bold"), foreground="#2E86C1")
        self.lbl_result.pack(side="left", padx=10)

    # --- UI 建設函數 ---
    def build_basic_tab(self):
        ttk.Label(self.tab_basic, text="輸入數學算式 (例如: 5*sin(3.14)):").pack(anchor="w", padx=20, pady=(20,5))
        self.entry_basic = ttk.Entry(self.tab_basic, font=("Consolas", 14))
        self.entry_basic.pack(fill="x", padx=20)

    def build_diff_tab(self):
        ttk.Label(self.tab_diff, text="函數 f(x):").pack(anchor="w", padx=20, pady=(15,2))
        self.entry_diff_f = ttk.Entry(self.tab_diff, font=("Consolas", 12))
        self.entry_diff_f.pack(fill="x", padx=20)
        
        ttk.Label(self.tab_diff, text="代入 x 值:").pack(anchor="w", padx=20, pady=(15,2))
        self.entry_diff_x = ttk.Entry(self.tab_diff, font=("Consolas", 12))
        self.entry_diff_x.pack(fill="x", padx=20)

    def build_int1_tab(self):
        ttk.Label(self.tab_int1, text="函數 f(x):").grid(row=0, column=0, sticky="w", padx=20, pady=(15,5))
        self.entry_int1_f = ttk.Entry(self.tab_int1, font=("Consolas", 12), width=30)
        self.entry_int1_f.grid(row=0, column=1, pady=(15,5), columnspan=3)

        ttk.Label(self.tab_int1, text="下限 (a):").grid(row=1, column=0, sticky="w", padx=20, pady=5)
        self.entry_int1_a = ttk.Entry(self.tab_int1, font=("Consolas", 12), width=10)
        self.entry_int1_a.grid(row=1, column=1, pady=5)

        ttk.Label(self.tab_int1, text="上限 (b):").grid(row=1, column=2, sticky="w", padx=10, pady=5)
        self.entry_int1_b = ttk.Entry(self.tab_int1, font=("Consolas", 12), width=10)
        self.entry_int1_b.grid(row=1, column=3, pady=5)

    def build_int2_tab(self):
        ttk.Label(self.tab_int2, text="函數 f(x,y):").grid(row=0, column=0, sticky="w", padx=20, pady=(15,5))
        self.entry_int2_f = ttk.Entry(self.tab_int2, font=("Consolas", 12), width=30)
        self.entry_int2_f.grid(row=0, column=1, pady=(15,5), columnspan=3)

        ttk.Label(self.tab_int2, text="X 下限/上限:").grid(row=1, column=0, sticky="w", padx=20, pady=5)
        self.entry_int2_ax = ttk.Entry(self.tab_int2, font=("Consolas", 12), width=10)
        self.entry_int2_ax.grid(row=1, column=1)
        self.entry_int2_bx = ttk.Entry(self.tab_int2, font=("Consolas", 12), width=10)
        self.entry_int2_bx.grid(row=1, column=2, padx=10)

        ttk.Label(self.tab_int2, text="Y 下限/上限:").grid(row=2, column=0, sticky="w", padx=20, pady=5)
        self.entry_int2_ay = ttk.Entry(self.tab_int2, font=("Consolas", 12), width=10)
        self.entry_int2_ay.grid(row=2, column=1)
        self.entry_int2_by = ttk.Entry(self.tab_int2, font=("Consolas", 12), width=10)
        self.entry_int2_by.grid(row=2, column=2, padx=10)

    def build_int3_tab(self):
        ttk.Label(self.tab_int3, text="函數 f(x,y,z):").grid(row=0, column=0, sticky="w", padx=20, pady=(10,5))
        self.entry_int3_f = ttk.Entry(self.tab_int3, font=("Consolas", 12), width=30)
        self.entry_int3_f.grid(row=0, column=1, pady=(10,5), columnspan=3)

        bounds = [("X", 1), ("Y", 2), ("Z", 3)]
        self.int3_entries = {}
        for axis, row in bounds:
            ttk.Label(self.tab_int3, text=f"{axis} 下限/上限:").grid(row=row, column=0, sticky="w", padx=20, pady=5)
            e1 = ttk.Entry(self.tab_int3, font=("Consolas", 12), width=10)
            e1.grid(row=row, column=1)
            e2 = ttk.Entry(self.tab_int3, font=("Consolas", 12), width=10)
            e2.grid(row=row, column=2, padx=10)
            self.int3_entries[axis] = (e1, e2)

    # --- 核心邏輯：與 C 語言引擎溝通 ---
    def calculate(self):
        current_tab = self.notebook.index(self.notebook.select())
        input_str = ""

        try:
            # 根據目前所在的分頁，組裝要餵給 C 程式的字串
            if current_tab == 0:
                input_str = f"{self.entry_basic.get()}\n"
            elif current_tab == 1:
                input_str = f"diff\n{self.entry_diff_f.get()}\n{self.entry_diff_x.get()}\n"
            elif current_tab == 2:
                input_str = f"int1\n{self.entry_int1_f.get()}\n{self.entry_int1_a.get()} {self.entry_int1_b.get()}\n"
            elif current_tab == 3:
                input_str = f"int2\n{self.entry_int2_f.get()}\n{self.entry_int2_ax.get()} {self.entry_int2_bx.get()}\n{self.entry_int2_ay.get()} {self.entry_int2_by.get()}\n"
            elif current_tab == 4:
                ex, ey, ez = self.int3_entries["X"], self.int3_entries["Y"], self.int3_entries["Z"]
                input_str = f"int3\n{self.entry_int3_f.get()}\n{ex[0].get()} {ex[1].get()}\n{ey[0].get()} {ey[1].get()}\n{ez[0].get()} {ez[1].get()}\n"

            input_str += "exit\n" # 告訴 C 程式結束執行

            # 呼叫 C 引擎
            exe_path = "financial_calc.exe" if sys.platform == "win32" else "./financial_calc"
            process = subprocess.run(
                [exe_path] if sys.platform == "win32" else ["./financial_calc"],
                input=input_str, capture_output=True, text=True, encoding='utf-8'
            )
            
            output = process.stdout
            
            # 使用 Regex 抓取最後的答案
            match = re.search(r'=>.*?(?:approx:|Result:)\s*([0-9.-]+)', output)
            if match:
                self.lbl_result.config(text=match.group(1), foreground="#2E86C1")
            else:
                self.lbl_result.config(text="語法錯誤或無法解析", foreground="#E74C3C")
                print("--- C Engine Debug Info ---")
                print(output)
                
        except Exception as e:
            self.lbl_result.config(text="執行錯誤，請檢查輸入或 C 引擎", foreground="#E74C3C")
            print("Error:", e)

if __name__ == "__main__":
    root = tk.Tk()
    app = CalculusGUI(root)
    root.mainloop()