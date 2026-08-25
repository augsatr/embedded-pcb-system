import "./globals.css";
import Navbar from "@/components/Navbar";
export const metadata = { title: "KrishiConnect - SIH 26132", description: "Market linkage & price discovery for farmers" };
export default function RootLayout({ children }: { children: React.ReactNode }){
  return (
    <html lang="en">
      <body className="min-h-screen">
        <Navbar />
        <main className="max-w-7xl mx-auto px-4 py-6">{children}</main>
        <footer className="text-center text-xs text-gray-400 py-6 border-t mt-8">Govt of Maharashtra • Maharashtra State Innovation Society • SIH 2026 PS 26132 • Prototype v0.1</footer>
      </body>
    </html>
  );
}
