"use client";
import Link from "next/link";
import { usePathname } from "next/navigation";
const nav = [
  { href:"/", label:"Dashboard" },
  { href:"/prices", label:"Live Prices" },
  { href:"/advisor", label:"Price Advisor" },
  { href:"/pool", label:"FPO Pooling" },
];
export default function Navbar(){
  const path = usePathname();
  return (
    <nav className="bg-white border-b sticky top-0 z-50">
      <div className="max-w-7xl mx-auto px-4 flex items-center h-14 gap-6">
        <div className="font-bold text-krishi-700 text-lg">🌾 KrishiConnect <span className="text-xs font-normal text-gray-500 ml-1">SIH26132</span></div>
        <div className="hidden md:flex gap-1">
          {nav.map(n=>(
            <Link key={n.href} href={n.href} className={`px-3 py-1.5 rounded text-sm ${path===n.href?"bg-krishi-600 text-white":"hover:bg-gray-100 text-gray-700"}`}>{n.label}</Link>
          ))}
        </div>
        <div className="ml-auto flex gap-2">
          <span className="text-xs bg-green-50 text-green-700 px-2 py-1 rounded border">👤 Ramesh (Junnar FPO)</span>
          <select className="text-xs border rounded px-1"><option>EN</option><option>मराठी</option><option>हिंदी</option></select>
        </div>
      </div>
    </nav>
  );
}
