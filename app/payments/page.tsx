export default function Payments(){
  return (
    <div className="space-y-4">
      <h1 className="text-xl font-bold">Payment Tracking & Grievance</h1>
      <div className="bg-white rounded-xl border overflow-hidden">
        <table className="w-full text-sm">
          <thead className="bg-gray-50 text-xs"><tr><th className="p-3 text-left">Transaction</th><th>Buyer</th><th>Amount</th><th>Status</th><th>Action</th></tr></thead>
          <tbody>
            <tr className="border-t"><td className="p-3"><div className="font-mono text-xs">TXN-8841</div><div className="text-xs">LOT-1023 • 12 MT Onion • 18 Aug</div></td><td className="text-center">Sahyadri Farms</td><td className="text-center font-bold">₹3,42,000</td><td className="text-center"><span className="bg-green-100 text-green-700 px-2 py-1 rounded text-xs">Paid ✓ 20 Aug</span></td><td className="text-center text-xs">UTR: 28371 • Receipt ↓</td></tr>
            <tr className="border-t"><td className="p-3"><div className="font-mono text-xs">TXN-8842</div><div className="text-xs">LOT-1025 • 40 MT Tur • 19 Aug</div></td><td className="text-center">Mid-Day Meal Auth</td><td className="text-center font-bold">₹40,80,000</td><td className="text-center"><span className="bg-amber-100 text-amber-700 px-2 py-1 rounded text-xs">Escrow - Due 23 Aug</span></td><td className="text-center"><button className="text-xs border px-2 py-1 rounded">Track</button></td></tr>
            <tr className="border-t bg-red-50"><td className="p-3"><div className="font-mono text-xs">TXN-8839</div><div className="text-xs">LOT-1022 • 8 MT Tomato • 10 Aug</div></td><td className="text-center">Local Trader (Unverified)</td><td className="text-center font-bold">₹1,20,000</td><td className="text-center"><span className="bg-red-100 text-red-700 px-2 py-1 rounded text-xs">Delayed 12 days</span></td><td className="text-center"><button className="text-xs bg-red-600 text-white px-2 py-1 rounded">Raise Grievance</button></td></tr>
          </tbody>
        </table>
      </div>
      <div className="grid md:grid-cols-2 gap-4">
        <div className="bg-white p-4 rounded-xl border">
          <h3 className="font-semibold text-sm">Escrow & Smart Contract</h3>
          <p className="text-xs text-gray-600 mt-1">Buyer deposits 100% on offer acceptance → funds locked → released on delivery confirmation (either party + transport OTP). Reduces non-payment from 12% to &lt;1% in pilot.</p>
          <div className="text-xs mt-2 p-2 bg-blue-50 rounded">UPI Autopay + eNACH + Ledger (immutable record for audit).</div>
        </div>
        <div className="bg-white p-4 rounded-xl border">
          <h3 className="font-semibold text-sm">Grievance Flow</h3>
          <ol className="text-xs list-decimal ml-5 mt-2 space-y-1">
            <li>Raise → auto-notify buyer + FPO mediator (48h window)</li>
            <li>Upload proof (weigh slip, quality photos, UTR)</li>
            <li>Escalate to APMC officer / MSRS single dashboard</li>
            <li>Resolution SLA 7 days • Penalty + buyer rating docked</li>
          </ol>
          <button className="mt-3 text-xs w-full border py-1.5 rounded">Demo: File Grievance for TXN-8839</button>
        </div>
      </div>
    </div>
  );
}
